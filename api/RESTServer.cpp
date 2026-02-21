#include "RESTServer.h"
#include "../auth/UserManager.h"
#include "../security/InputValidator.h"
#include "../currency/ExchangeRates.h"
#include "../fees/FeeEngine.h"
#include "HTTPServer.h"
#include "WalletEndpoints.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <sstream>

namespace {
std::string jsonEscape(const std::string &s) {
  std::string out;
  out.reserve(s.size());
  for (char c : s) {
    switch (c) {
    case '\\':
      out += "\\\\";
      break;
    case '"':
      out += "\\\"";
      break;
    case '\r':
      out += "\\r";
      break;
    case '\n':
      out += "\\n";
      break;
    case '\t':
      out += "\\t";
      break;
    default:
      out.push_back(c);
      break;
    }
  }
  return out;
}

std::string extractJsonStringField(const std::string &body,
                                  const std::string &field) {
  // Some clients (notably certain PowerShell quoting patterns) can send JSON
  // with escaped quotes like {\"username\":\"x\"} or even double-escaped.
  // To keep dependencies at zero, we normalize by removing backslashes and then
  // search the plain JSON pattern.
  std::string normalized;
  normalized.reserve(body.size());
  for (char c : body) {
    if (c != '\\') {
      normalized.push_back(c);
    }
  }

  // Try strict token first: "field"
  const std::string strictToken = "\"" + field + "\"";
  size_t pos = normalized.find(strictToken);
  size_t tokenLen = strictToken.size();

  // Fallback: loose token: field
  if (pos == std::string::npos) {
    pos = normalized.find(field);
    tokenLen = field.size();
    if (pos == std::string::npos) {
      return "";
    }
  }

  // Find ':' after the token
  pos = normalized.find(':', pos + tokenLen);
  if (pos == std::string::npos) {
    return "";
  }
  ++pos;

  // Skip whitespace
  while (pos < normalized.size() &&
         (normalized[pos] == ' ' || normalized[pos] == '\t' ||
          normalized[pos] == '\r' || normalized[pos] == '\n')) {
    ++pos;
  }

  // Value can be quoted or unquoted.
  if (pos < normalized.size() && normalized[pos] == '"') {
    const size_t start = pos + 1;
    size_t end = normalized.find('"', start);
    if (end == std::string::npos) {
      return "";
    }
    return normalized.substr(start, end - start);
  }

  // Unquoted: read until ',' or '}'
  const size_t start = pos;
  size_t end = start;
  while (end < normalized.size() && normalized[end] != ',' &&
         normalized[end] != '}' && normalized[end] != '\r' &&
         normalized[end] != '\n') {
    ++end;
  }
  if (end == start) {
    return "";
  }

  // Trim trailing whitespace
  while (end > start &&
         (normalized[end - 1] == ' ' || normalized[end - 1] == '\t')) {
    --end;
  }

  return normalized.substr(start, end - start);
}

double extractJsonNumberField(const std::string &body, const std::string &field,
                              bool &found) {
  found = false;
  std::string normalized;
  normalized.reserve(body.size());
  for (char c : body) {
    if (c != '\\') {
      normalized.push_back(c);
    }
  }

  const std::string strictToken = "\"" + field + "\"";
  size_t pos = normalized.find(strictToken);
  size_t tokenLen = strictToken.size();
  if (pos == std::string::npos) {
    pos = normalized.find(field);
    tokenLen = field.size();
    if (pos == std::string::npos) {
      return 0.0;
    }
  }

  pos = normalized.find(':', pos + tokenLen);
  if (pos == std::string::npos) {
    return 0.0;
  }
  ++pos;

  while (pos < normalized.size() &&
         (normalized[pos] == ' ' || normalized[pos] == '\t' ||
          normalized[pos] == '\r' || normalized[pos] == '\n')) {
    ++pos;
  }

  // Allow quoted numeric too
  if (pos < normalized.size() && normalized[pos] == '"') {
    ++pos;
  }

  size_t end = pos;
  while (end < normalized.size()) {
    const char c = normalized[end];
    if (!(std::isdigit(static_cast<unsigned char>(c)) || c == '.' || c == '-' ||
          c == '+' || c == 'e' || c == 'E')) {
      break;
    }
    ++end;
  }
  if (end == pos) {
    return 0.0;
  }

  try {
    const double value = std::stod(normalized.substr(pos, end - pos));
    found = true;
    return value;
  } catch (...) {
    return 0.0;
  }
}
} // namespace


RESTServer::RESTServer(WalletEndpoints &endpoints)
    : walletEndpoints(endpoints), running(false), serverPort(0) {}

RESTServer::~RESTServer() { stop(); }

void RESTServer::run(int port) {
  serverPort = port;
  running = true;

  auto httpServer = std::make_unique<HTTPServer>(port);
  auto userMgr = std::make_shared<UserManager>(walletEndpoints.getDatabase());
  ExchangeRates exchangeRates;
  auto &db = walletEndpoints.getDatabase();
  auto &mtx = walletEndpoints.getMutex();
  auto &engine = walletEndpoints.getTransactionEngine();
  auto &fraud = walletEndpoints.getFraudDetector();
  auto &limits = walletEndpoints.getTransactionLimits();
  FeeEngine feeEngine;

  // Register all endpoints
  httpServer->registerRoute(
      "GET", "/api/v1/health",
      [](const std::string &, const std::string &,
         const std::string &) -> std::string {
        return "{\"status\":\"healthy\",\"version\":\"1.0.1\"}";
      });

  httpServer->registerRoute(
      "POST", "/api/v1/users/signup",
      [userMgr](const std::string &, const std::string &,
                const std::string &body) -> std::string {
        std::string user, pass;
        user = InputValidator::sanitizeString(
            extractJsonStringField(body, "username"));
        pass = InputValidator::sanitizeString(
            extractJsonStringField(body, "password"));

        if (!user.empty() && !InputValidator::isValidUsername(user)) {
          return std::string(
              "{\"success\":false,\"error\":\"Invalid username format\"}");
        }

        if (!pass.empty() && !InputValidator::isValidPassword(pass)) {
          return std::string(
              "{\"success\":false,\"error\":\"Password must be 8+ chars with uppercase, lowercase, digit, and special character\"}");
        }

        if (user.empty() || pass.empty()) {
          std::string snippet = body.substr(0, 200);
          return std::string(
              "{\"success\":false,\"error\":\"Missing username or password\",\"receivedBody\":\"" +
              jsonEscape(snippet) + "\"}");
        }
        
        std::string email = InputValidator::sanitizeString(
            extractJsonStringField(body, "email"));
        if (!email.empty() && !InputValidator::isValidEmail(email)) {
          return std::string(
              "{\"success\":false,\"error\":\"Invalid email format\"}");
        }
        
        std::string uid = userMgr->signup(user, pass, email);
        if (uid.empty())
          return std::string("{\"success\":false,\"error\":\"User exists\"}");
        return std::string("{\"success\":true,\"userId\":\"" + uid + "\"}");
      });

  httpServer->registerRoute(
      "POST", "/api/v1/auth/login",
      [userMgr](const std::string &, const std::string &,
                const std::string &body) -> std::string {
        std::string user, pass;
        user = InputValidator::sanitizeString(
            extractJsonStringField(body, "username"));
        pass = InputValidator::sanitizeString(
            extractJsonStringField(body, "password"));

        if (!user.empty() && !InputValidator::isValidUsername(user)) {
          return std::string(
              "{\"success\":false,\"error\":\"Invalid username format\"}");
        }

        if (user.empty() || pass.empty()) {
          std::string snippet = body.substr(0, 200);
          return std::string(
              "{\"success\":false,\"error\":\"Missing username or password\",\"receivedBody\":\"" +
              jsonEscape(snippet) + "\"}");
        }
        std::string token = userMgr->login(user, pass);
        if (token.empty())
          return std::string("{\"success\":false,\"error\":\"Invalid credentials\"}");
        return std::string("{\"success\":true,\"token\":\"" + token +
                           "\",\"expiresIn\":3600}");
      });

  httpServer->registerRoute("POST", "/api/v1/wallets",
                            [&db, &mtx](const std::string &, const std::string &,
                               const std::string &body) -> std::string {
                              try {
                                  std::string currency = InputValidator::sanitizeString(
                                      extractJsonStringField(body, "currency"));
                                  if (currency.empty()) {
                                      std::string snippet = body.substr(0, 200);
                                      return std::string(
                                          "{\"success\":false,\"error\":\"Missing currency parameter\",\"receivedBody\":\"" +
                                          jsonEscape(snippet) + "\"}");
                                  }
                                  
                                  // Validate currency
                                  if (currency != "USD" && currency != "EUR" && currency != "KES" && currency != "BTC") {
                                      return "{\"success\":false,\"error\":\"Unsupported currency. Use USD, EUR, KES, or BTC\"}";
                                  }
                                  
                                  // Generate unique wallet ID
                                  std::ostringstream walletId;
                                  walletId << "wallet_" << time(0) << "_" << rand();
                                  
                                  // Create wallet in database
                                  std::lock_guard<std::mutex> lock(mtx);
                                  db.createWallet(walletId.str(), currency);
                                  
                                  std::ostringstream response;
                                  response << "{\"success\":true,\"walletId\":\"" << walletId.str() 
                                           << "\",\"currency\":\"" << currency 
                                           << "\",\"balance\":0.0}";
                                  return response.str();
                                  
                              } catch (const std::exception &e) {
                                  return std::string("{\"success\":false,\"error\":\"") + e.what() + "\"}";
                              }
                            });

  httpServer->registerRoute("POST", "/api/v1/wallets/{id}/deposit",
                            [&db, &mtx](const std::string &, const std::string &path,
                               const std::string &body) -> std::string {
                              try {
                                const std::string normalizedPath =
                                    HTTPServer::stripQueryString(path);
                                const auto parts = HTTPServer::splitPath(normalizedPath);
                                if (parts.size() < 5) {
                                  return "{\"success\":false,\"error\":\"Invalid path\"}";
                                }
                                const std::string walletId = parts[3];

                                bool foundAmount = false;
                                const double amount =
                                    extractJsonNumberField(body, "amount", foundAmount);
                                if (!foundAmount || amount <= 0.0) {
                                  return "{\"success\":false,\"error\":\"Missing or invalid amount\"}";
                                }

                                std::lock_guard<std::mutex> lock(mtx);
                                if (!db.walletExists(walletId)) {
                                  return "{\"success\":false,\"error\":\"Wallet not found\"}";
                                }

                                const double bal = db.getBalance(walletId);
                                db.updateBalance(walletId, bal + amount);
                                const std::string currency = db.getWalletCurrency(walletId);
                                std::ostringstream r;
                                r << "{\"success\":true,\"walletId\":\"" << walletId
                                  << "\",\"balance\":" << (bal + amount) << ",\"currency\":\""
                                  << (currency.empty() ? "USD" : currency) << "\"}";
                                return r.str();
                              } catch (const std::exception &e) {
                                return std::string("{\"success\":false,\"error\":\"") + e.what() + "\"}";
                              }
                            });

  httpServer->registerRoute("POST", "/api/v1/wallets/{id}/withdraw",
                            [&db, &mtx](const std::string &, const std::string &path,
                               const std::string &body) -> std::string {
                              try {
                                const std::string normalizedPath =
                                    HTTPServer::stripQueryString(path);
                                const auto parts = HTTPServer::splitPath(normalizedPath);
                                if (parts.size() < 5) {
                                  return "{\"success\":false,\"error\":\"Invalid path\"}";
                                }
                                const std::string walletId = parts[3];

                                bool foundAmount = false;
                                const double amount =
                                    extractJsonNumberField(body, "amount", foundAmount);
                                if (!foundAmount || amount <= 0.0) {
                                  return "{\"success\":false,\"error\":\"Missing or invalid amount\"}";
                                }

                                std::lock_guard<std::mutex> lock(mtx);
                                if (!db.walletExists(walletId)) {
                                  return "{\"success\":false,\"error\":\"Wallet not found\"}";
                                }

                                const double bal = db.getBalance(walletId);
                                if (bal < amount) {
                                  return "{\"success\":false,\"error\":\"Insufficient funds\"}";
                                }
                                db.updateBalance(walletId, bal - amount);
                                const std::string currency = db.getWalletCurrency(walletId);
                                std::ostringstream r;
                                r << "{\"success\":true,\"walletId\":\"" << walletId
                                  << "\",\"balance\":" << (bal - amount) << ",\"currency\":\""
                                  << (currency.empty() ? "USD" : currency) << "\"}";
                                return r.str();
                              } catch (const std::exception &e) {
                                return std::string("{\"success\":false,\"error\":\"") + e.what() + "\"}";
                              }
                            });

  httpServer->registerRoute("GET", "/api/v1/wallets/{id}/transactions",
                            [&db, &mtx](const std::string &, const std::string &path,
                               const std::string &) -> std::string {
                              try {
                                  // Expected: /api/v1/wallets/{id}/transactions
                                  const std::string normalized = HTTPServer::stripQueryString(path);
                                  const auto parts = HTTPServer::splitPath(normalized);
                                  if (parts.size() < 5) {
                                      return "{\"success\":false,\"error\":\"Invalid path\"}";
                                  }

                                  const std::string walletId = parts[3];
                                  int limit = 50;

                                  // Parse optional query param: ?limit=
                                  size_t limitPos = path.find("limit=");
                                  if (limitPos != std::string::npos) {
                                      size_t limitStart = limitPos + 6;
                                      size_t limitEnd = path.find("&", limitStart);
                                      if (limitEnd == std::string::npos) limitEnd = path.length();
                                      try {
                                          limit = std::stoi(path.substr(limitStart, limitEnd - limitStart));
                                          limit = std::min(limit, 100);
                                      } catch (...) {
                                          limit = 50;
                                      }
                                  }

                                  std::lock_guard<std::mutex> lock(mtx);
                                  auto transactions = db.getTransactionHistory(walletId);

                                  std::ostringstream response;
                                  response << "{\"success\":true,\"walletId\":\"" << walletId
                                           << "\",\"transactions\":[";

                                  int count = 0;
                                  for (const auto &tx : transactions) {
                                      if (count >= limit) break;
                                      if (count > 0) response << ",";
                                      response << "{\"id\":\"" << tx.at("id")
                                               << "\",\"from\":\"" << tx.at("from")
                                               << "\",\"to\":\"" << tx.at("to")
                                               << "\",\"amount\":" << tx.at("amount")
                                               << ",\"fee\":" << (tx.count("fee") ? tx.at("fee") : std::string("0"))
                                               << ",\"timestamp\":" << tx.at("timestamp") << "}";
                                      count++;
                                  }

                                  response << "],\"total\":" << transactions.size() << "}";
                                  return response.str();
                              } catch (const std::exception &e) {
                                  return std::string("{\"success\":false,\"error\":\"") + e.what() + "\"}";
                              }
                            });

  httpServer->registerRoute("GET", "/api/v1/wallets/balance",
                            [&db, &mtx](const std::string &, const std::string &path,
                               const std::string &) -> std::string {
                              try {
                                  // Extract wallet ID from path or use default
                                  std::string walletId = "wallet_123"; // Default for testing
                                  
                                  // Parse wallet ID from query parameters if present
                                  size_t walletPos = path.find("walletId=");
                                  if (walletPos != std::string::npos) {
                                      size_t start = walletPos + 9;
                                      size_t end = path.find("&", start);
                                      if (end == std::string::npos) end = path.length();
                                      walletId = path.substr(start, end - start);
                                  }
                                  
                                  std::lock_guard<std::mutex> lock(mtx);
                                  double balance = db.getBalance(walletId);
                                  std::string currency = db.getWalletCurrency(walletId);
                                  if (currency.empty()) {
                                      currency = "USD";
                                  }
                                  
                                  std::ostringstream response;
                                  response << "{\"walletId\":\"" << walletId 
                                           << "\",\"balance\":" << balance 
                                           << ",\"currency\":\"" << currency << "\"}";
                                  return response.str();
                                  
                              } catch (const std::exception &e) {
                                  return std::string("{\"success\":false,\"error\":\"") + e.what() + "\"}";
                              }
                            });

  httpServer->registerRoute("GET", "/api/v1/wallets/{id}/balance",
                            [&db, &mtx](const std::string &, const std::string &path,
                               const std::string &) -> std::string {
                              try {
                                  // Expected: /api/v1/wallets/{id}/balance
                                  const std::string normalized = HTTPServer::stripQueryString(path);
                                  const auto parts = HTTPServer::splitPath(normalized);
                                  if (parts.size() < 5) {
                                      return "{\"success\":false,\"error\":\"Invalid path\"}";
                                  }

                                  const std::string walletId = parts[3];
                                  std::lock_guard<std::mutex> lock(mtx);
                                  double balance = db.getBalance(walletId);
                                  std::string currency = db.getWalletCurrency(walletId);
                                  if (currency.empty()) {
                                      currency = "USD";
                                  }

                                  std::ostringstream response;
                                  response << "{\"walletId\":\"" << walletId
                                           << "\",\"balance\":" << balance
                                           << ",\"currency\":\"" << currency << "\"}";
                                  return response.str();
                              } catch (const std::exception &e) {
                                  return std::string("{\"success\":false,\"error\":\"") + e.what() + "\"}";
                              }
                            });

  httpServer->registerRoute("GET", "/api/v1/wallets/transactions",
                            [&db, &mtx](const std::string &, const std::string &path,
                               const std::string &) -> std::string {
                              try {
                                  // Extract wallet ID from query parameters
                                  size_t walletPos = path.find("walletId=");
                                  if (walletPos == std::string::npos) {
                                      return "{\"success\":false,\"error\":\"Missing walletId parameter\"}";
                                  }
                                  
                                  size_t start = walletPos + 9;
                                  size_t end = path.find("&", start);
                                  if (end == std::string::npos) end = path.length();
                                  std::string walletId = path.substr(start, end - start);
                                  
                                  // Extract limit parameter (optional)
                                  int limit = 50; // Default limit
                                  size_t limitPos = path.find("limit=");
                                  if (limitPos != std::string::npos) {
                                      size_t limitStart = limitPos + 6;
                                      size_t limitEnd = path.find("&", limitStart);
                                      if (limitEnd == std::string::npos) limitEnd = path.length();
                                      try {
                                          limit = std::stoi(path.substr(limitStart, limitEnd - limitStart));
                                          limit = std::min(limit, 100); // Max 100 transactions
                                      } catch (...) {
                                          limit = 50; // Use default if invalid
                                      }
                                  }
                                  
                                  std::lock_guard<std::mutex> lock(mtx);
                                  auto transactions = db.getTransactionHistory(walletId);
                                  
                                  std::ostringstream response;
                                  response << "{\"success\":true,\"walletId\":\"" << walletId 
                                           << "\",\"transactions\":[";
                                  
                                  int count = 0;
                                  for (const auto& tx : transactions) {
                                      if (count >= limit) break;
                                      
                                      if (count > 0) response << ",";
                                      
                                      response << "{\"id\":\"" << tx.at("id") 
                                               << "\",\"from\":\"" << tx.at("from") 
                                               << "\",\"to\":\"" << tx.at("to") 
                                               << "\",\"amount\":" << tx.at("amount") 
                                               << ",\"fee\":" << (tx.count("fee") ? tx.at("fee") : std::string("0"))
                                               << ",\"timestamp\":" << tx.at("timestamp") << "}";
                                      count++;
                                  }
                                  
                                  response << "],\"total\":" << transactions.size() << "}";
                                  return response.str();
                                  
                              } catch (const std::exception &e) {
                                  return std::string("{\"success\":false,\"error\":\"") + e.what() + "\"}";
                              }
                            });

  httpServer->registerRoute("GET", "/api/v1/convert",
                            [&exchangeRates](const std::string &, const std::string &path,
                               const std::string &) -> std::string {
                              // Extract query parameters from path
                              size_t fromPos = path.find("from=");
                              size_t toPos = path.find("to=");
                              size_t amountPos = path.find("amount=");
                              
                              if (fromPos != std::string::npos && toPos != std::string::npos && amountPos != std::string::npos) {
                                  std::string from = path.substr(fromPos + 5, path.find("&", fromPos) - fromPos - 5);
                                  std::string to = path.substr(toPos + 3, path.find("&", toPos) - toPos - 3);
                                  std::string amountStr = path.substr(amountPos + 7);

                                  try {
                                      double amount = std::stod(amountStr);
                                      if (amount <= 0) {
                                          return "{\"success\":false,\"error\":\"Amount must be positive\"}";
                                      }

                                      double rate = exchangeRates.getRate(from, to);
                                      if (rate <= 0.0) {
                                          return "{\"success\":false,\"error\":\"Rate unavailable\"}";
                                      }

                                      int spreadBps = 20;
                                      const char *env = std::getenv("VMS_FX_SPREAD_BPS");
                                      if (env && *env) {
                                          try {
                                              spreadBps = std::stoi(std::string(env));
                                          } catch (...) {
                                              spreadBps = 20;
                                          }
                                      }
                                      if (spreadBps < 0) spreadBps = 0;
                                      if (spreadBps > 500) spreadBps = 500;

                                      const double spreadMultiplier = 1.0 - (static_cast<double>(spreadBps) / 10000.0);
                                      const double effectiveRate = rate * spreadMultiplier;
                                      const double result = amount * effectiveRate;

                                      const std::string pair = from + "/" + to;
                                      const std::string ts = exchangeRates.getRateTimestamp(pair);
                                      
                                      std::ostringstream r;
                                      r << "{\"success\":true,\"from\":\"" << from 
                                         << "\",\"to\":\"" << to 
                                         << "\",\"amount\":" << amount 
                                         << ",\"result\":" << result 
                                         << ",\"rate\":" << effectiveRate 
                                         << ",\"midRate\":" << rate
                                         << ",\"spreadBps\":" << spreadBps
                                         << ",\"providerTimestamp\":\"" << ts << "\""
                                         << ",\"timestamp\":" << time(0) << "}";
                                      return r.str();
                                  } catch (...) {
                                      return "{\"success\":false,\"error\":\"Invalid amount\"}";
                                  }
                              }
                              return "{\"success\":false,\"error\":\"Missing parameters\"}";
                            });

  httpServer->registerRoute("POST", "/api/v1/transactions",
                            [&db, &engine, &mtx, &fraud, &limits, &feeEngine](const std::string &, const std::string &,
                               const std::string &body) -> std::string {
                              try {
                                  std::string fromWallet = InputValidator::sanitizeString(
                                      extractJsonStringField(body, "fromWallet"));
                                  std::string toWallet = InputValidator::sanitizeString(
                                      extractJsonStringField(body, "toWallet"));
                                  bool foundAmount = false;
                                  double amount = extractJsonNumberField(body, "amount", foundAmount);

                                  if (fromWallet.empty() || toWallet.empty() || !foundAmount) {
                                      return "{\"success\":false,\"error\":\"Missing required fields: fromWallet, toWallet, amount\"}";
                                  }
                                  
                                  // Validate amount
                                  if (amount <= 0) {
                                      return "{\"success\":false,\"error\":\"Amount must be positive\"}";
                                  }

                                  const double fee = feeEngine.calculateFee("transfer", amount);
                                  const double totalDebit = amount + fee;
                                  
                                  if (!limits.isWithinLimit(amount)) {
                                      return "{\"success\":false,\"error\":\"Transaction amount exceeds limit\"}";
                                  }
                                  
                                  std::lock_guard<std::mutex> lock(mtx);
                                  
                                  if (!db.walletExists(fromWallet) || !db.walletExists(toWallet)) {
                                      return "{\"success\":false,\"error\":\"Wallet not found\"}";
                                  }

                                  // Check balances
                                  double fromBalance = db.getBalance(fromWallet);
                                  if (fromBalance < totalDebit) {
                                      return "{\"success\":false,\"error\":\"Insufficient funds\"}";
                                  }
                                  
                                  // Perform fraud detection
                                  if (fraud.isSuspiciousTransaction(fromWallet, toWallet, amount)) {
                                      return "{\"success\":false,\"error\":\"Transaction flagged for review\"}";
                                  }
                                  
                                  // Process transaction
                                  db.updateBalance(fromWallet, fromBalance - totalDebit);
                                  double toBalance = db.getBalance(toWallet);
                                  db.updateBalance(toWallet, toBalance + amount);

                                  // Collect fee into a treasury wallet
                                  std::string treasuryWallet = "treasury_" + db.getWalletCurrency(fromWallet);
                                  if (treasuryWallet == "treasury_") {
                                    treasuryWallet = "treasury_USD";
                                  }
                                  if (!db.walletExists(treasuryWallet)) {
                                    db.createWallet(treasuryWallet, db.getWalletCurrency(fromWallet).empty()
                                                                 ? "USD"
                                                                 : db.getWalletCurrency(fromWallet));
                                  }
                                  const double treasuryBal = db.getBalance(treasuryWallet);
                                  db.updateBalance(treasuryWallet, treasuryBal + fee);
                                  
                                  // Generate transaction ID
                                  std::ostringstream txId;
                                  txId << "tx_" << time(0) << "_" << rand();
                                  
                                  // Save transaction
                                  db.saveTransaction(txId.str(), fromWallet, toWallet, amount, fee);
                                  
                                  std::ostringstream response;
                                  response << "{\"success\":true,\"transactionId\":\"" << txId.str()
                                           << "\",\"status\":\"completed\",\"amount\":" << amount
                                           << ",\"fee\":" << fee
                                           << ",\"totalDebited\":" << totalDebit << "}";
                                  return response.str();
                                  
                              } catch (const std::exception &e) {
                                  return std::string("{\"success\":false,\"error\":\"") + e.what() + "\"}";
                              }
                            });

  std::cout << "\n========================================\n";
  std::cout << "VirtualMoneySystem API Server\n";
  std::cout << "========================================\n";
  std::cout << "Port: " << port << "\n";
  std::cout << "URL: http://localhost:" << port << "\n";
  std::cout << "========================================\n\n";
  std::cout << "Endpoints:\n";
  std::cout << "  GET  /api/v1/health\n";
  std::cout << "  POST /api/v1/users/signup\n";
  std::cout << "  POST /api/v1/auth/login\n";
  std::cout << "  POST /api/v1/wallets\n";
  std::cout << "  GET  /api/v1/wallets/balance\n";
  std::cout << "  GET  /api/v1/wallets/transactions\n";
  std::cout << "  GET  /api/v1/convert\n";
  std::cout << "  POST /api/v1/transactions\n\n";

  httpServer->start();

  while (running && httpServer->isRunning()) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  httpServer->stop();
}

void RESTServer::stop() {
  running = false;
  std::cout << "[API] Server stopped\n";
}

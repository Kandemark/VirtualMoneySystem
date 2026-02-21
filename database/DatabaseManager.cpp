#include "DatabaseManager.h"
#include <ctime>
#include <iostream>
#include <sstream>


DatabaseManager::DatabaseManager(const std::string &path) : dbPath(path) {}

DatabaseManager::~DatabaseManager() {}

void DatabaseManager::initialize() {
  std::lock_guard<std::mutex> lock(dbMutex);
  // In-memory initialization - no external DB
  std::cout << "[DB] Initialized in-memory database: " << dbPath << std::endl;
}

bool DatabaseManager::execute(const std::string &query) {
  std::lock_guard<std::mutex> lock(dbMutex);
  // Stub implementation
  return true;
}

bool DatabaseManager::walletExists(const std::string &walletId) {
  std::lock_guard<std::mutex> lock(dbMutex);
  return wallets.find(walletId) != wallets.end();
}

std::vector<std::map<std::string, std::string>>
DatabaseManager::query(const std::string &sql) {
  std::lock_guard<std::mutex> lock(dbMutex);
  return std::vector<std::map<std::string, std::string>>();
}

bool DatabaseManager::createWallet(const std::string &userId,
                                   const std::string &currency) {
  std::lock_guard<std::mutex> lock(dbMutex);
  // NOTE: Despite parameter name `userId`, this method is used throughout the
  // codebase with a generated wallet identifier. We treat the first argument as
  // the walletId.
  const std::string &walletId = userId;
  wallets[walletId] = 0.0;
  walletCurrencies[walletId] = currency;
  std::cout << "[DB] Created wallet: " << walletId << " (" << currency << ")" << std::endl;
  return true;
}

double DatabaseManager::getBalance(const std::string &walletId) {
  std::lock_guard<std::mutex> lock(dbMutex);
  auto it = wallets.find(walletId);
  return (it != wallets.end()) ? it->second : 0.0;
}

bool DatabaseManager::updateBalance(const std::string &walletId,
                                    double newBalance) {
  std::lock_guard<std::mutex> lock(dbMutex);
  wallets[walletId] = newBalance;
  return true;
}

std::string DatabaseManager::getWalletCurrency(const std::string &walletId) {
  std::lock_guard<std::mutex> lock(dbMutex);
  auto it = walletCurrencies.find(walletId);
  return (it != walletCurrencies.end()) ? it->second : "";
}

std::map<std::string, double> DatabaseManager::getAllWalletBalances() {
  std::lock_guard<std::mutex> lock(dbMutex);
  return wallets;
}

std::map<std::string, std::string> DatabaseManager::getAllWalletCurrencies() {
  std::lock_guard<std::mutex> lock(dbMutex);
  return walletCurrencies;
}

bool DatabaseManager::saveTransaction(const std::string &txId,
                                      const std::string &from,
                                      const std::string &to, double amount) {
  std::lock_guard<std::mutex> lock(dbMutex);
  std::map<std::string, std::string> tx;
  tx["id"] = txId;
  tx["from"] = from;
  tx["to"] = to;
  tx["amount"] = std::to_string(amount);

  tx["fee"] = std::to_string(0.0);

  time_t now = time(0);
  tx["timestamp"] = std::to_string(now);

  transactions.push_back(tx);
  return true;
}

bool DatabaseManager::saveTransaction(const std::string &txId,
                                      const std::string &from,
                                      const std::string &to, double amount,
                                      double fee) {
  std::lock_guard<std::mutex> lock(dbMutex);
  std::map<std::string, std::string> tx;
  tx["id"] = txId;
  tx["from"] = from;
  tx["to"] = to;
  tx["amount"] = std::to_string(amount);
  tx["fee"] = std::to_string(fee);

  time_t now = time(0);
  tx["timestamp"] = std::to_string(now);

  transactions.push_back(tx);
  return true;
}

std::vector<std::map<std::string, std::string>>
DatabaseManager::getTransactionHistory(const std::string &walletId) {
  std::lock_guard<std::mutex> lock(dbMutex);
  std::vector<std::map<std::string, std::string>> result;

  for (const auto &tx : transactions) {
    if (tx.at("from") == walletId || tx.at("to") == walletId) {
      result.push_back(tx);
    }
  }

  return result;
}

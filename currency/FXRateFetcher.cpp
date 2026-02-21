
#include "FXRateFetcher.h"

#include <algorithm>
#include <cctype>
#include <sstream>
#include <stdexcept>
#include <vector>

#include <windows.h>
#include <winhttp.h>

#pragma comment(lib, "winhttp.lib")

namespace {

std::wstring toWide(const std::string &s) {
  return std::wstring(s.begin(), s.end());
}

std::string httpGet(const std::wstring &host, INTERNET_PORT port,
                    const std::wstring &path, bool useHttps) {
  HINTERNET hSession = WinHttpOpen(L"VirtualMoneySystem/1.0",
                                  WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
                                  WINHTTP_NO_PROXY_NAME,
                                  WINHTTP_NO_PROXY_BYPASS, 0);
  if (!hSession) {
    throw std::runtime_error("WinHttpOpen failed");
  }

  HINTERNET hConnect = WinHttpConnect(hSession, host.c_str(), port, 0);
  if (!hConnect) {
    WinHttpCloseHandle(hSession);
    throw std::runtime_error("WinHttpConnect failed");
  }

  DWORD flags = useHttps ? WINHTTP_FLAG_SECURE : 0;
  HINTERNET hRequest = WinHttpOpenRequest(hConnect, L"GET", path.c_str(),
                                         NULL, WINHTTP_NO_REFERER,
                                         WINHTTP_DEFAULT_ACCEPT_TYPES, flags);
  if (!hRequest) {
    WinHttpCloseHandle(hConnect);
    WinHttpCloseHandle(hSession);
    throw std::runtime_error("WinHttpOpenRequest failed");
  }

  BOOL ok = WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0,
                               WINHTTP_NO_REQUEST_DATA, 0, 0, 0);
  if (ok) {
    ok = WinHttpReceiveResponse(hRequest, NULL);
  }
  if (!ok) {
    WinHttpCloseHandle(hRequest);
    WinHttpCloseHandle(hConnect);
    WinHttpCloseHandle(hSession);
    throw std::runtime_error("HTTP request failed");
  }

  std::string result;
  DWORD available = 0;
  do {
    available = 0;
    if (!WinHttpQueryDataAvailable(hRequest, &available)) {
      break;
    }
    if (available == 0) {
      break;
    }
    std::vector<char> buffer(available);
    DWORD read = 0;
    if (!WinHttpReadData(hRequest, buffer.data(), available, &read)) {
      break;
    }
    result.append(buffer.data(), buffer.data() + read);
  } while (available > 0);

  WinHttpCloseHandle(hRequest);
  WinHttpCloseHandle(hConnect);
  WinHttpCloseHandle(hSession);
  return result;
}

// Very small JSON helpers (not a general JSON parser)
// Extracts a number after:  "KEY": <number>
bool extractJsonNumber(const std::string &json, const std::string &key,
                       double &out) {
  const std::string needle = "\"" + key + "\":";
  size_t pos = json.find(needle);
  if (pos == std::string::npos) {
    return false;
  }
  pos += needle.size();
  while (pos < json.size() && std::isspace(static_cast<unsigned char>(json[pos]))) {
    ++pos;
  }
  size_t end = pos;
  while (end < json.size()) {
    char c = json[end];
    if (!(std::isdigit(static_cast<unsigned char>(c)) || c == '.' || c == '-' ||
          c == '+' || c == 'e' || c == 'E')) {
      break;
    }
    ++end;
  }
  if (end == pos) {
    return false;
  }
  try {
    out = std::stod(json.substr(pos, end - pos));
    return true;
  } catch (...) {
    return false;
  }
}

std::string upper(std::string s) {
  std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) {
    return static_cast<char>(std::toupper(c));
  });
  return s;
}

std::string pairKey(const std::string &from, const std::string &to) {
  return upper(from) + "/" + upper(to);
}

} // namespace

void FXRateFetcher::setAPIKey(const std::string &provider,
                              const std::string &apiKey) {
  apiKeys[provider] = apiKey;
}

bool FXRateFetcher::testConnection(const std::string &provider) {
  try {
    (void)fetchRates(provider);
    return true;
  } catch (...) {
    return false;
  }
}

std::map<std::string, double>
FXRateFetcher::fetchRates(const std::string &provider) {
  // Default strategy (no keys):
  // - Fiat base USD from er-api
  // - BTC price from CoinGecko

  const std::string prov = provider.empty() ? "default" : provider;
  std::map<std::string, double> out;

  if (prov == "default" || prov == "ERAPI") {
    // https://open.er-api.com/v6/latest/USD
    const std::string json = httpGet(L"open.er-api.com", 443,
                                     L"/v6/latest/USD", true);

    // Extract a few currencies we care about. We can extend later.
    double eur = 0.0, kes = 0.0;
    bool okEur = extractJsonNumber(json, "EUR", eur);
    bool okKes = extractJsonNumber(json, "KES", kes);

    // USD base
    if (okEur) {
      out[pairKey("USD", "EUR")] = eur;
      out[pairKey("EUR", "USD")] = 1.0 / eur;
    }
    if (okKes) {
      out[pairKey("USD", "KES")] = kes;
      out[pairKey("KES", "USD")] = 1.0 / kes;
    }

    out[pairKey("USD", "USD")] = 1.0;
    if (okEur) {
      out[pairKey("EUR", "EUR")] = 1.0;
    }
    if (okKes) {
      out[pairKey("KES", "KES")] = 1.0;
    }

    // Crosses
    if (okEur && okKes) {
      // EUR/KES = (USD/KES) / (USD/EUR)
      out[pairKey("EUR", "KES")] = kes / eur;
      out[pairKey("KES", "EUR")] = eur / kes;
    }
  }

  if (prov == "default" || prov == "COINGECKO") {
    // https://api.coingecko.com/api/v3/simple/price?ids=bitcoin&vs_currencies=usd,eur
    const std::string json = httpGet(
        L"api.coingecko.com", 443,
        L"/api/v3/simple/price?ids=bitcoin&vs_currencies=usd,eur", true);

    // Response shape: {"bitcoin":{"usd":40000,"eur":36800}}
    // We'll just extract "usd" and "eur" numbers (lowercase in response).
    double usd = 0.0, eur = 0.0;
    bool okUsd = extractJsonNumber(json, "usd", usd);
    bool okEur = extractJsonNumber(json, "eur", eur);

    if (okUsd && usd > 0) {
      out[pairKey("BTC", "USD")] = usd;
      out[pairKey("USD", "BTC")] = 1.0 / usd;
    }
    if (okEur && eur > 0) {
      out[pairKey("BTC", "EUR")] = eur;
      out[pairKey("EUR", "BTC")] = 1.0 / eur;
    }

    out[pairKey("BTC", "BTC")] = 1.0;
  }

  if (out.empty()) {
    throw std::runtime_error("No rates fetched");
  }

  return out;
}

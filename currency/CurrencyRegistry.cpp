
#include "CurrencyRegistry.h"

#include <algorithm>
#include <mutex>

namespace {
std::mutex g_curMutex;

std::string upper(std::string s) {
  std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) {
    return static_cast<char>(std::toupper(c));
  });
  return s;
}
} // namespace

void CurrencyRegistry::registerCurrency(const Currency &currency) {
  std::lock_guard<std::mutex> lock(g_curMutex);
  Currency c = currency;
  c.code = upper(c.code);
  currencies[c.code] = c;
}

Currency CurrencyRegistry::getCurrency(const std::string &code) {
  std::lock_guard<std::mutex> lock(g_curMutex);

  if (currencies.empty()) {
    // Register defaults on first use.
    currencies["USD"] = Currency{"USD", "US Dollar", "$", 2};
    currencies["EUR"] = Currency{"EUR", "Euro", "€", 2};
    currencies["KES"] = Currency{"KES", "Kenyan Shilling", "KSh", 2};
    currencies["BTC"] = Currency{"BTC", "Bitcoin", "₿", 8};
  }

  const std::string key = upper(code);
  auto it = currencies.find(key);
  if (it != currencies.end()) {
    return it->second;
  }
  return Currency{};
}

std::vector<std::string> CurrencyRegistry::getSupportedCurrencies() {
  std::lock_guard<std::mutex> lock(g_curMutex);
  if (currencies.empty()) {
    (void)getCurrency("USD");
  }
  std::vector<std::string> out;
  out.reserve(currencies.size());
  for (const auto &pair : currencies) {
    out.push_back(pair.first);
  }
  return out;
}

bool CurrencyRegistry::isSupported(const std::string &code) {
  std::lock_guard<std::mutex> lock(g_curMutex);
  if (currencies.empty()) {
    (void)getCurrency("USD");
  }
  return currencies.find(upper(code)) != currencies.end();
}

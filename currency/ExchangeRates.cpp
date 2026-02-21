
#include "ExchangeRates.h"

#include "FXCacheManager.h"
#include "FXRateFetcher.h"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <stdexcept>

namespace {
std::string nowTimestampUtc() {
  std::time_t t = std::time(nullptr);
  std::tm tm{};
#if defined(_WIN32)
  gmtime_s(&tm, &t);
#else
  gmtime_r(&t, &tm);
#endif

  std::ostringstream oss;
  oss << std::put_time(&tm, "%Y-%m-%dT%H:%M:%SZ");
  return oss.str();
}

std::string pairKey(const std::string &from, const std::string &to) {
  return from + "/" + to;
}

} // namespace

double ExchangeRates::getRate(const std::string &fromCurrency,
                              const std::string &toCurrency) {
  const std::string key = pairKey(fromCurrency, toCurrency);

  // 1) Cache fast path
  FXCacheManager cache;
  const double cached = cache.getCachedRate(key);
  if (cached > 0.0) {
    return cached;
  }

  // 2) If we already have in-memory (from last fetchLatestRates), use it
  {
    std::lock_guard<std::mutex> lock(ratesMutex);
    auto it = rates.find(key);
    if (it != rates.end() && it->second > 0.0) {
      cache.cacheRate(key, it->second, 300);
      return it->second;
    }
  }

  // 3) Fetch now (realtime)
  fetchLatestRates();
  {
    std::lock_guard<std::mutex> lock(ratesMutex);
    auto it = rates.find(key);
    if (it != rates.end()) {
      cache.cacheRate(key, it->second, 300);
      return it->second;
    }
  }

  return 0.0;
}

void ExchangeRates::updateRate(const std::string &currencyPair, double rate) {
  if (rate <= 0.0) {
    return;
  }
  std::lock_guard<std::mutex> lock(ratesMutex);
  rates[currencyPair] = rate;
  timestamps[currencyPair] = nowTimestampUtc();

  // Keep cache warm
  FXCacheManager cache;
  cache.cacheRate(currencyPair, rate, 300);
}

void ExchangeRates::fetchLatestRates() {
  FXRateFetcher fetcher;
  const auto fetched = fetcher.fetchRates("default");
  const std::string ts = nowTimestampUtc();

  {
    std::lock_guard<std::mutex> lock(ratesMutex);
    for (const auto &pair : fetched) {
      rates[pair.first] = pair.second;
      timestamps[pair.first] = ts;
    }
  }

  FXCacheManager cache;
  for (const auto &pair : fetched) {
    cache.cacheRate(pair.first, pair.second, 300);
  }
}

std::string ExchangeRates::getRateTimestamp(const std::string &currencyPair) {
  std::lock_guard<std::mutex> lock(ratesMutex);
  auto it = timestamps.find(currencyPair);
  if (it == timestamps.end()) {
    return "";
  }
  return it->second;
}

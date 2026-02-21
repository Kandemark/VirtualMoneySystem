
#include "FXCacheManager.h"

#include <chrono>
#include <map>
#include <mutex>

namespace {
struct CacheEntry {
  double rate = 0.0;
  std::chrono::steady_clock::time_point expiresAt{};
};

std::mutex g_cacheMutex;
std::map<std::string, CacheEntry> g_cache;
} // namespace

double FXCacheManager::getCachedRate(const std::string &currencyPair) {
  std::lock_guard<std::mutex> lock(g_cacheMutex);
  auto it = g_cache.find(currencyPair);
  if (it == g_cache.end()) {
    return 0.0;
  }
  if (std::chrono::steady_clock::now() > it->second.expiresAt) {
    g_cache.erase(it);
    return 0.0;
  }
  return it->second.rate;
}

void FXCacheManager::cacheRate(const std::string &currencyPair, double rate,
                              int ttlSeconds) {
  if (ttlSeconds <= 0) {
    ttlSeconds = 300;
  }

  std::lock_guard<std::mutex> lock(g_cacheMutex);
  CacheEntry entry;
  entry.rate = rate;
  entry.expiresAt = std::chrono::steady_clock::now() +
                    std::chrono::seconds(ttlSeconds);
  g_cache[currencyPair] = entry;
}

void FXCacheManager::clearCache() {
  std::lock_guard<std::mutex> lock(g_cacheMutex);
  g_cache.clear();
}

bool FXCacheManager::isCached(const std::string &currencyPair) {
  std::lock_guard<std::mutex> lock(g_cacheMutex);
  auto it = g_cache.find(currencyPair);
  if (it == g_cache.end()) {
    return false;
  }
  return std::chrono::steady_clock::now() <= it->second.expiresAt;
}

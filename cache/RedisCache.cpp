/**
 * @file RedisCache.cpp
 */

#include "RedisCache.h"
#include <iostream>

namespace VirtualMoney {

RedisCache::RedisCache() : hits(0), misses(0) {}

bool RedisCache::set(const std::string& key, const std::string& value, int ttlSeconds) {
    CacheEntry entry;
    entry.value = value;
    entry.expiry = std::chrono::system_clock::now() + std::chrono::seconds(ttlSeconds);
    
    cache[key] = entry;
    
    std::cout << "Cache SET: " << key << " (TTL: " << ttlSeconds << "s)" << std::endl;
    
    return true;
}

std::string RedisCache::get(const std::string& key) {
    auto it = cache.find(key);
    
    if (it == cache.end()) {
        misses++;
        std::cout << "Cache MISS: " << key << std::endl;
        return "";
    }
    
    if (isExpired(it->second)) {
        cache.erase(it);
        misses++;
        std::cout << "Cache MISS (expired): " << key << std::endl;
        return "";
    }
    
    hits++;
    std::cout << "Cache HIT: " << key << std::endl;
    return it->second.value;
}

bool RedisCache::del(const std::string& key) {
    auto it = cache.find(key);
    if (it != cache.end()) {
        cache.erase(it);
        std::cout << "Cache DEL: " << key << std::endl;
        return true;
    }
    return false;
}

bool RedisCache::exists(const std::string& key) {
    auto it = cache.find(key);
    if (it != cache.end() && !isExpired(it->second)) {
        return true;
    }
    return false;
}

long long RedisCache::incr(const std::string& key) {
    std::string value = get(key);
    long long num = value.empty() ? 0 : std::stoll(value);
    num++;
    
    set(key, std::to_string(num));
    
    return num;
}

bool RedisCache::setex(const std::string& key, int seconds, const std::string& value) {
    return set(key, value, seconds);
}

RedisCache::CacheStats RedisCache::getStats() const {
    CacheStats stats;
    stats.hits = hits;
    stats.misses = misses;
    stats.totalKeys = cache.size();
    
    long long total = hits + misses;
    stats.hitRate = total > 0 ? (static_cast<double>(hits) / total) * 100.0 : 0.0;
    
    return stats;
}

void RedisCache::flushAll() {
    cache.clear();
    std::cout << "Cache FLUSHED" << std::endl;
}

bool RedisCache::isExpired(const CacheEntry& entry) {
    return std::chrono::system_clock::now() > entry.expiry;
}

void RedisCache::cleanupExpired() {
    auto it = cache.begin();
    while (it != cache.end()) {
        if (isExpired(it->second)) {
            it = cache.erase(it);
        } else {
            ++it;
        }
    }
}

} // namespace VirtualMoney

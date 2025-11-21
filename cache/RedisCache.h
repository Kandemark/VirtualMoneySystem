/**
 * @file RedisCache.h
 * @brief Redis caching layer for 10x performance
 */

#ifndef REDIS_CACHE_H
#define REDIS_CACHE_H

#include <string>
#include <map>
#include <chrono>

namespace VirtualMoney {

struct CacheEntry {
    std::string value;
    std::chrono::system_clock::time_point expiry;
};

class RedisCache {
public:
    RedisCache();
    
    /**
     * @brief Set cache value with TTL
     */
    bool set(const std::string& key, const std::string& value, int ttlSeconds = 300);
    
    /**
     * @brief Get cache value
     */
    std::string get(const std::string& key);
    
    /**
     * @brief Delete cache key
     */
    bool del(const std::string& key);
    
    /**
     * @brief Check if key exists
     */
    bool exists(const std::string& key);
    
    /**
     * @brief Increment counter
     */
    long long incr(const std::string& key);
    
    /**
     * @brief Set with expiry time
     */
    bool setex(const std::string& key, int seconds, const std::string& value);
    
    /**
     * @brief Get cache statistics
     */
    struct CacheStats {
        long long hits;
        long long misses;
        long long totalKeys;
        double hitRate;
    };
    
    CacheStats getStats() const;
    
    /**
     * @brief Clear all cache
     */
    void flushAll();
    
private:
    std::map<std::string, CacheEntry> cache;
    long long hits;
    long long misses;
    
    bool isExpired(const CacheEntry& entry);
    void cleanupExpired();
};

} // namespace VirtualMoney

#endif

/**
 * @file FXCacheManager.h
 * @brief FX rate caching for performance
 */

#ifndef FX_CACHE_MANAGER_H
#define FX_CACHE_MANAGER_H

#include <string>
#include <map>

/**
 * @brief Caches FX rates for performance
 */
class FXCacheManager {
public:
    /**
     * @brief Get cached rate
     * @param currencyPair Currency pair
     * @return Cached rate (0 if not found)
     */
    double getCachedRate(const std::string& currencyPair);
    
    /**
     * @brief Cache rate
     * @param currencyPair Currency pair
     * @param rate Exchange rate
     * @param ttlSeconds Time to live in seconds
     */
    void cacheRate(const std::string& currencyPair, double rate, int ttlSeconds = 300);
    
    /**
     * @brief Clear cache
     */
    void clearCache();
    
    /**
     * @brief Check if rate is cached and valid
     * @param currencyPair Currency pair
     * @return true if valid cached rate exists
     */
    bool isCached(const std::string& currencyPair);

private:
    std::map<std::string, double> cache;
};

#endif

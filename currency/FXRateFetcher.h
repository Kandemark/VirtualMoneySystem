/**
 * @file FXRateFetcher.h
 * @brief Fetch FX rates from external providers
 */

#ifndef FX_RATE_FETCHER_H
#define FX_RATE_FETCHER_H

#include <string>
#include <map>

/**
 * @brief Fetches FX rates from external sources
 */
class FXRateFetcher {
public:
    /**
     * @brief Fetch rates from provider
     * @param provider Provider name (e.g., "ECB", "OpenExchangeRates")
     * @return Map of currency pairs to rates
     */
    std::map<std::string, double> fetchRates(const std::string& provider = "default");
    
    /**
     * @brief Set API key for provider
     * @param provider Provider name
     * @param apiKey API key
     */
    void setAPIKey(const std::string& provider, const std::string& apiKey);
    
    /**
     * @brief Test provider connection
     * @param provider Provider name
     * @return true if connection successful
     */
    bool testConnection(const std::string& provider);

private:
    std::map<std::string, std::string> apiKeys;
};

#endif

/**
 * @file CurrencyRegistry.h
 * @brief Registry of supported currencies
 */

#ifndef CURRENCY_REGISTRY_H
#define CURRENCY_REGISTRY_H

#include <string>
#include <vector>
#include <map>

/**
 * @brief Currency information
 */
struct Currency {
    std::string code;
    std::string name;
    std::string symbol;
    int decimals;
};

/**
 * @brief Manages currency registry
 */
class CurrencyRegistry {
public:
    /**
     * @brief Register currency
     * @param currency Currency details
     */
    void registerCurrency(const Currency& currency);
    
    /**
     * @brief Get currency info
     * @param code Currency code
     * @return Currency information
     */
    Currency getCurrency(const std::string& code);
    
    /**
     * @brief Get all supported currencies
     * @return Vector of currency codes
     */
    std::vector<std::string> getSupportedCurrencies();
    
    /**
     * @brief Check if currency is supported
     * @param code Currency code
     * @return true if supported
     */
    bool isSupported(const std::string& code);

private:
    std::map<std::string, Currency> currencies;
};

#endif

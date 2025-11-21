/**
 * @file ConversionEngine.h
 * @brief Currency conversion engine
 */

#ifndef CONVERSION_ENGINE_H
#define CONVERSION_ENGINE_H

#include <string>

/**
 * @brief Handles currency conversions
 */
class ConversionEngine {
public:
    /**
     * @brief Convert currency
     * @param amount Amount to convert
     * @param fromCurrency Source currency code
     * @param toCurrency Target currency code
     * @return Converted amount
     */
    double convert(double amount, const std::string& fromCurrency, const std::string& toCurrency);
    
    /**
     * @brief Get conversion rate
     * @param fromCurrency Source currency
     * @param toCurrency Target currency
     * @return Exchange rate
     */
    double getRate(const std::string& fromCurrency, const std::string& toCurrency);
    
    /**
     * @brief Update exchange rates
     */
    void updateRates();
};

#endif

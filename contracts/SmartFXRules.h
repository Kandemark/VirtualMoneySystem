/**
 * @file SmartFXRules.h
 * @brief Smart FX conversion rules
 */

#ifndef SMART_FX_RULES_H
#define SMART_FX_RULES_H

#include <string>

/**
 * @brief Intelligent FX conversion rules
 */
class SmartFXRules {
public:
    /**
     * @brief Apply smart FX rules
     * @param fromCurrency Source currency
     * @param toCurrency Target currency
     * @param amount Amount to convert
     * @return Optimized conversion amount
     */
    double applyRules(const std::string& fromCurrency, const std::string& toCurrency, double amount);
    
    /**
     * @brief Get best conversion time
     * @param currencyPair Currency pair
     * @return Recommended time
     */
    std::string getBestConversionTime(const std::string& currencyPair);
    
    /**
     * @brief Set conversion threshold
     * @param threshold Minimum amount for smart conversion
     */
    void setThreshold(double threshold);
};

#endif

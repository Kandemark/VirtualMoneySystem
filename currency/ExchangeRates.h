/**
 * @file ExchangeRates.h
 * @brief Real-time exchange rate management
 */

#ifndef EXCHANGE_RATES_H
#define EXCHANGE_RATES_H

#include <string>
#include <map>

/**
 * @brief Manages exchange rates
 */
class ExchangeRates {
public:
    /**
     * @brief Get exchange rate
     * @param fromCurrency Source currency
     * @param toCurrency Target currency
     * @return Exchange rate
     */
    double getRate(const std::string& fromCurrency, const std::string& toCurrency);
    
    /**
     * @brief Update rate
     * @param currencyPair Currency pair (e.g., "USD/EUR")
     * @param rate New rate
     */
    void updateRate(const std::string& currencyPair, double rate);
    
    /**
     * @brief Fetch latest rates from provider
     */
    void fetchLatestRates();
    
    /**
     * @brief Get rate timestamp
     * @param currencyPair Currency pair
     * @return Last update timestamp
     */
    std::string getRateTimestamp(const std::string& currencyPair);

private:
    std::map<std::string, double> rates;
};

#endif

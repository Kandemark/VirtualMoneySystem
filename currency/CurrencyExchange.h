#ifndef CURRENCY_EXCHANGE_H
#define CURRENCY_EXCHANGE_H

#include <string>
#include <map>
#include <vector>

class CurrencyExchange {
public:
    CurrencyExchange();
    
    // Convert amount from one currency to another
    double convert(const std::string& fromCurrency, const std::string& toCurrency, double amount) const;
    
    // Get exchange rate between two currencies
    double getExchangeRate(const std::string& fromCurrency, const std::string& toCurrency) const;
    
    // Update exchange rate (for admin purposes)
    void updateExchangeRate(const std::string& fromCurrency, const std::string& toCurrency, double rate);
    
    // Get all supported currencies
    std::vector<std::string> getSupportedCurrencies() const;
    
    // Check if currency is supported
    bool isSupportedCurrency(const std::string& currency) const;
    
    // Get market volatility index (0.0 - 1.0)
    double getVolatilityIndex() const;
    
    // Simulate market fluctuations
    void simulateMarketFluctuation();

private:
    // Exchange rates stored as base currency -> target currency -> rate
    std::map<std::string, std::map<std::string, double>> exchangeRates;
    
    // Initialize default exchange rates
    void initializeDefaultRates();
    
    // Validate currency codes
    bool isValidCurrencyCode(const std::string& currency) const;
    
    // Calculate cross rate when direct rate doesn't exist
    double calculateCrossRate(const std::string& fromCurrency, const std::string& toCurrency) const;
};

#endif // CURRENCY_EXCHANGE_H

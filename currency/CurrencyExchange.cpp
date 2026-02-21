#include "CurrencyExchange.h"
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <cmath>

CurrencyExchange::CurrencyExchange() {
    initializeDefaultRates();
}

double CurrencyExchange::convert(const std::string& fromCurrency, const std::string& toCurrency, double amount) const {
    if (amount <= 0) return 0.0;
    
    if (fromCurrency == toCurrency) return amount;
    
    if (!isValidCurrencyCode(fromCurrency) || !isValidCurrencyCode(toCurrency)) {
        return 0.0;
    }
    
    double rate = getExchangeRate(fromCurrency, toCurrency);
    return amount * rate;
}

double CurrencyExchange::getExchangeRate(const std::string& fromCurrency, const std::string& toCurrency) const {
    if (fromCurrency == toCurrency) return 1.0;
    
    // Check for direct exchange rate
    auto fromIt = exchangeRates.find(fromCurrency);
    if (fromIt != exchangeRates.end()) {
        auto toIt = fromIt->second.find(toCurrency);
        if (toIt != fromIt->second.end()) {
            return toIt->second;
        }
    }
    
    // Try reverse rate
    auto reverseFromIt = exchangeRates.find(toCurrency);
    if (reverseFromIt != exchangeRates.end()) {
        auto reverseToIt = reverseFromIt->second.find(fromCurrency);
        if (reverseToIt != reverseFromIt->second.end()) {
            return 1.0 / reverseToIt->second;
        }
    }
    
    // Calculate cross rate through USD as base
    return calculateCrossRate(fromCurrency, toCurrency);
}

void CurrencyExchange::updateExchangeRate(const std::string& fromCurrency, const std::string& toCurrency, double rate) {
    if (!isValidCurrencyCode(fromCurrency) || !isValidCurrencyCode(toCurrency) || rate <= 0) {
        return;
    }
    
    exchangeRates[fromCurrency][toCurrency] = rate;
    
    // Update reverse rate
    exchangeRates[toCurrency][fromCurrency] = 1.0 / rate;
}

std::vector<std::string> CurrencyExchange::getSupportedCurrencies() const {
    std::vector<std::string> currencies;
    for (const auto& pair : exchangeRates) {
        currencies.push_back(pair.first);
    }
    return currencies;
}

bool CurrencyExchange::isSupportedCurrency(const std::string& currency) const {
    return isValidCurrencyCode(currency) && exchangeRates.find(currency) != exchangeRates.end();
}

double CurrencyExchange::getVolatilityIndex() const {
    // Calculate volatility based on recent rate changes
    // For now, return a simulated value
    return 0.15 + (rand() % 100) / 1000.0; // 0.15 to 0.25
}

void CurrencyExchange::simulateMarketFluctuation() {
    // Simulate small random changes in exchange rates
    for (auto& fromPair : exchangeRates) {
        for (auto& toPair : fromPair.second) {
            // Skip if it's the same currency
            if (fromPair.first == toPair.first) continue;
            
            // Apply random fluctuation between -2% and +2%
            double fluctuation = 1.0 + ((rand() % 400 - 200) / 10000.0); // -0.02 to +0.02
            toPair.second *= fluctuation;
            
            // Ensure rate stays within reasonable bounds
            if (toPair.second < 0.001) toPair.second = 0.001;
            if (toPair.second > 10000) toPair.second = 10000;
        }
    }
}

void CurrencyExchange::initializeDefaultRates() {
    // Base currency is USD
    
    // USD rates
    exchangeRates["USD"]["EUR"] = 0.92;
    exchangeRates["USD"]["KES"] = 152.50;
    exchangeRates["USD"]["BTC"] = 0.000025;
    
    // EUR rates
    exchangeRates["EUR"]["USD"] = 1.09;
    exchangeRates["EUR"]["KES"] = 165.80;
    exchangeRates["EUR"]["BTC"] = 0.000027;
    
    // KES rates
    exchangeRates["KES"]["USD"] = 0.0066;
    exchangeRates["KES"]["EUR"] = 0.0060;
    exchangeRates["KES"]["BTC"] = 0.00000016;
    
    // BTC rates
    exchangeRates["BTC"]["USD"] = 40000.0;
    exchangeRates["BTC"]["EUR"] = 36800.0;
    exchangeRates["BTC"]["KES"] = 6100000.0;
    
    // Self rates (1:1)
    exchangeRates["USD"]["USD"] = 1.0;
    exchangeRates["EUR"]["EUR"] = 1.0;
    exchangeRates["KES"]["KES"] = 1.0;
    exchangeRates["BTC"]["BTC"] = 1.0;
}

bool CurrencyExchange::isValidCurrencyCode(const std::string& currency) const {
    return currency == "USD" || currency == "EUR" || currency == "KES" || currency == "BTC";
}

double CurrencyExchange::calculateCrossRate(const std::string& fromCurrency, const std::string& toCurrency) const {
    // Try to find a path through USD as the base currency
    if (fromCurrency != "USD" && toCurrency != "USD") {
        double fromToUSD = getExchangeRate(fromCurrency, "USD");
        double USDToTarget = getExchangeRate("USD", toCurrency);
        
        if (fromToUSD > 0 && USDToTarget > 0) {
            return fromToUSD * USDToTarget;
        }
    }
    
    // If no path found, return 1:1 as fallback
    return 1.0;
}

#include "ExchangeRates.h"
#include <stdexcept>

ExchangeRates::ExchangeRates() {
    initializeDefaultRates();
}

void ExchangeRates::setRate(const std::string& from, const std::string& to, double rate) {
    auto key = std::make_pair(from, to);
    rates[key] = {from, to, rate, std::chrono::system_clock::now()};
    
    // Also set the inverse rate
    auto inverseKey = std::make_pair(to, from);
    rates[inverseKey] = {to, from, 1.0 / rate, std::chrono::system_clock::now()};
}

double ExchangeRates::getRate(const std::string& from, const std::string& to) const {
    if (from == to) {
        return 1.0;
    }
    
    auto key = std::make_pair(from, to);
    auto it = rates.find(key);
    
    if (it == rates.end()) {
        throw std::runtime_error("Exchange rate not available for " + from + " to " + to);
    }
    
    return it->second.rate;
}

double ExchangeRates::convert(double amount, const std::string& from, const std::string& to) const {
    return amount * getRate(from, to);
}

bool ExchangeRates::hasRate(const std::string& from, const std::string& to) const {
    if (from == to) {
        return true;
    }
    
    auto key = std::make_pair(from, to);
    return rates.find(key) != rates.end();
}

std::string ExchangeRates::getRateKey(const std::string& from, const std::string& to) const {
    return from + "_" + to;
}

void ExchangeRates::initializeDefaultRates() {
    // Initialize some common exchange rates
    setRate("USD", "EUR", 0.92);
    setRate("USD", "GBP", 0.79);
    setRate("USD", "JPY", 149.50);
    setRate("EUR", "GBP", 0.86);
    setRate("BTC", "USD", 43000.0);
    setRate("ETH", "USD", 2300.0);
}

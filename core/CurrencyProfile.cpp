#include "CurrencyProfile.h"
#include <string>
#include <iostream>
#include <stdexcept>

// Constructor
CurrencyProfile::CurrencyProfile(const std::string& name, const std::string& symbol, double initialRate)
    : currencyName(name), currencySymbol(symbol), exchangeRate(initialRate) 
{
    if (currencyName.empty()) {
        throw std::invalid_argument("Currency name cannot be empty.");
    }
    if (currencySymbol.empty()) {
        throw std::invalid_argument("Currency symbol cannot be empty.");
    }
    if (exchangeRate <= 0.0) {
        throw std::invalid_argument("Exchange rate must be positive.");
    }
}

// Getter for currency name
std::string CurrencyProfile::getName() const {
    return currencyName;
}

// Getter for currency symbol
std::string CurrencyProfile::getSymbol() const {
    return currencySymbol;
}

// Getter for exchange rate
double CurrencyProfile::getExchangeRate() const {
    return exchangeRate;
}

// Setter for exchange rate
void CurrencyProfile::setExchangeRate(double rate) {
    if (rate <= 0.0) {
        throw std::invalid_argument("Exchange rate must be positive.");
    }
    exchangeRate = rate;
}

// Print currency profile details
void CurrencyProfile::printProfile() const {
    std::cout << "Currency: " << currencyName
              << " (" << currencySymbol << "), Rate: "
              << exchangeRate << std::endl;
}

// Compare two currency profiles for equality
bool CurrencyProfile::operator==(const CurrencyProfile& other) const {
    return getName() == other.getName() &&
           getSymbol() == other.getSymbol() &&
           getExchangeRate() == other.getExchangeRate();
}

// Compare two currency profiles for inequality
bool CurrencyProfile::operator!=(const CurrencyProfile& other) const {
    return !(*this == other);
}

// Update all fields at once
void CurrencyProfile::updateProfile(const std::string& name, const std::string& symbol, double rate) {
    if (name.empty()) {
        throw std::invalid_argument("Currency name cannot be empty.");
    }
    if (symbol.empty()) {
        throw std::invalid_argument("Currency symbol cannot be empty.");
    }
    if (rate <= 0.0) {
        throw std::invalid_argument("Exchange rate must be positive.");
    }
    currencyName = name;
    currencySymbol = symbol;
    exchangeRate = rate;
}
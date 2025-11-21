/**
 * @file CurrencyCrisisManager.cpp
 */

#include "CurrencyCrisisManager.h"
#include <iostream>
#include <cmath>

namespace VirtualMoney {

CurrencyCrisisManager::CurrencyCrisisManager() {}

void CurrencyCrisisManager::monitorCurrency(const std::string& currency) {
    CurrencyStatus status;
    status.currency = currency;
    status.exchangeRate = 1.0;
    status.inflationRate = calculateInflationRate(currency);
    status.volatility = calculateVolatility(currency);
    status.capitalControlsActive = false;
    
    // Determine status
    if (status.inflationRate > 50.0) {
        status.status = "crisis";
    } else if (status.inflationRate > 10.0 || status.volatility > 20.0) {
        status.status = "warning";
    } else {
        status.status = "stable";
    }
    
    currencyStatuses[currency] = status;
    
    std::cout << "Monitoring " << currency 
              << " - Status: " << status.status 
              << " (Inflation: " << status.inflationRate << "%)" << std::endl;
}

CurrencyStatus CurrencyCrisisManager::getCurrencyStatus(const std::string& currency) {
    auto it = currencyStatuses.find(currency);
    if (it != currencyStatuses.end()) {
        return it->second;
    }
    return CurrencyStatus();
}

bool CurrencyCrisisManager::detectHyperinflation(const std::string& currency) {
    auto it = currencyStatuses.find(currency);
    if (it != currencyStatuses.end()) {
        // Hyperinflation: >50% per month
        if (it->second.inflationRate > 50.0) {
            std::cout << "HYPERINFLATION DETECTED: " << currency 
                      << " (" << it->second.inflationRate << "% monthly)" << std::endl;
            return true;
        }
    }
    return false;
}

bool CurrencyCrisisManager::activateCapitalControls(const std::string& currency) {
    auto it = currencyStatuses.find(currency);
    if (it != currencyStatuses.end()) {
        it->second.capitalControlsActive = true;
        
        std::cout << "Capital controls activated for " << currency << std::endl;
        std::cout << "- Withdrawal limits: $1,000/day" << std::endl;
        std::cout << "- Foreign exchange restrictions: Active" << std::endl;
        
        return true;
    }
    return false;
}

bool CurrencyCrisisManager::autoConvertToStable(const std::string& fromCurrency, 
                                                const std::string& toCurrency) {
    std::cout << "Auto-converting " << fromCurrency 
              << " to " << toCurrency << " (stable currency)" << std::endl;
    
    // Automatically convert user balances to stable currency
    return true;
}

std::vector<std::string> CurrencyCrisisManager::getRecommendedActions(const std::string& currency) {
    std::vector<std::string> actions;
    
    auto it = currencyStatuses.find(currency);
    if (it == currencyStatuses.end()) {
        return actions;
    }
    
    if (it->second.status == "crisis") {
        actions.push_back("Activate capital controls");
        actions.push_back("Auto-convert to USD/EUR");
        actions.push_back("Freeze new transactions");
        actions.push_back("Notify all users");
    } else if (it->second.status == "warning") {
        actions.push_back("Increase monitoring frequency");
        actions.push_back("Recommend hedging");
        actions.push_back("Alert high-value accounts");
    }
    
    return actions;
}

double CurrencyCrisisManager::calculateInflationRate(const std::string& currency) {
    // Simplified inflation calculation
    // In production, fetch from central bank APIs
    
    if (currency == "VEF") return 150.0;  // Venezuela
    if (currency == "ZWL") return 200.0;  // Zimbabwe
    if (currency == "LBP") return 80.0;   // Lebanon
    if (currency == "TRY") return 60.0;   // Turkey
    
    return 2.0; // Default 2%
}

double CurrencyCrisisManager::calculateVolatility(const std::string& currency) {
    // Calculate price volatility
    // In production, use historical data
    
    if (currency == "BTC") return 50.0;
    if (currency == "ETH") return 45.0;
    
    return 5.0; // Default 5%
}

} // namespace VirtualMoney

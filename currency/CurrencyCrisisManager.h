/**
 * @file CurrencyCrisisManager.h
 * @brief Currency crisis detection and management
 */

#ifndef CURRENCY_CRISIS_MANAGER_H
#define CURRENCY_CRISIS_MANAGER_H

#include <string>
#include <vector>
#include <map>

namespace VirtualMoney {

struct CurrencyStatus {
    std::string currency;
    double exchangeRate;
    double inflationRate;
    double volatility;
    std::string status;            // "stable", "warning", "crisis"
    bool capitalControlsActive;
};

class CurrencyCrisisManager {
public:
    CurrencyCrisisManager();
    
    void monitorCurrency(const std::string& currency);
    CurrencyStatus getCurrencyStatus(const std::string& currency);
    
    bool detectHyperinflation(const std::string& currency);
    bool activateCapitalControls(const std::string& currency);
    bool autoConvertToStable(const std::string& fromCurrency, const std::string& toCurrency);
    
    std::vector<std::string> getRecommendedActions(const std::string& currency);
    
private:
    std::map<std::string, CurrencyStatus> currencyStatuses;
    
    double calculateInflationRate(const std::string& currency);
    double calculateVolatility(const std::string& currency);
};

} // namespace VirtualMoney

#endif

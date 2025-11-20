#ifndef CURRENCY_REGISTRY_H
#define CURRENCY_REGISTRY_H

#include <string>
#include <vector>
#include <map>

struct CurrencyInfo {
    std::string code;
    std::string name;
    std::string symbol;
    int decimalPlaces;
};

class CurrencyRegistry {
public:
    CurrencyRegistry();

    void registerCurrency(const CurrencyInfo& currency);
    bool isCurrencySupported(const std::string& code) const;
    CurrencyInfo getCurrencyInfo(const std::string& code) const;
    std::vector<std::string> getAllCurrencies() const;

private:
    std::map<std::string, CurrencyInfo> currencies;
    void initializeDefaultCurrencies();
};

#endif // CURRENCY_REGISTRY_H

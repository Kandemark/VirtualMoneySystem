#include "CurrencyRegistry.h"
#include <stdexcept>

CurrencyRegistry::CurrencyRegistry() {
    initializeDefaultCurrencies();
}

void CurrencyRegistry::registerCurrency(const CurrencyInfo& currency) {
    currencies[currency.code] = currency;
}

bool CurrencyRegistry::isCurrencySupported(const std::string& code) const {
    return currencies.find(code) != currencies.end();
}

CurrencyInfo CurrencyRegistry::getCurrencyInfo(const std::string& code) const {
    auto it = currencies.find(code);
    if (it == currencies.end()) {
        throw std::runtime_error("Currency not supported: " + code);
    }
    return it->second;
}

std::vector<std::string> CurrencyRegistry::getAllCurrencies() const {
    std::vector<std::string> codes;
    for (const auto& [code, info] : currencies) {
        codes.push_back(code);
    }
    return codes;
}

void CurrencyRegistry::initializeDefaultCurrencies() {
    registerCurrency({"USD", "US Dollar", "$", 2});
    registerCurrency({"EUR", "Euro", "€", 2});
    registerCurrency({"GBP", "British Pound", "£", 2});
    registerCurrency({"JPY", "Japanese Yen", "¥", 0});
    registerCurrency({"BTC", "Bitcoin", "₿", 8});
    registerCurrency({"ETH", "Ethereum", "Ξ", 18});
}

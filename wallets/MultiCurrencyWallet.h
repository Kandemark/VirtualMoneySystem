/**
 * @file MultiCurrencyWallet.h
 * @brief Multi-currency wallet support
 */

#ifndef MULTI_CURRENCY_WALLET_H
#define MULTI_CURRENCY_WALLET_H

#include <string>
#include <map>
#include <vector>

class MultiCurrencyWallet {
public:
    MultiCurrencyWallet(const std::string& walletId);
    
    void addCurrency(const std::string& currencyCode);
    void removeCurrency(const std::string& currencyCode);
    
    double getBalance(const std::string& currencyCode);
    void deposit(const std::string& currencyCode, double amount);
    bool withdraw(const std::string& currencyCode, double amount);
    
    std::vector<std::string> getSupportedCurrencies();
    std::map<std::string, double> getAllBalances();
    
    bool convertCurrency(const std::string& fromCurrency, const std::string& toCurrency, double amount);

private:
    std::string walletId;
    std::map<std::string, double> currencyBalances;
};

#endif

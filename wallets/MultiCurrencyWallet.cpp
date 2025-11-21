/**
 * @file MultiCurrencyWallet.cpp
 */

#include "MultiCurrencyWallet.h"
#include <iostream>

namespace VirtualMoney {

MultiCurrencyWallet::MultiCurrencyWallet(const std::string& walletId, const std::string& userId)
    : walletId(walletId), userId(userId) {}

bool MultiCurrencyWallet::addCurrency(const std::string& currency) {
    if (balances.find(currency) == balances.end()) {
        balances[currency] = 0.0;
        std::cout << "Currency added: " << currency << std::endl;
        return true;
    }
    return false;
}

double MultiCurrencyWallet::getBalance(const std::string& currency) const {
    auto it = balances.find(currency);
    if (it != balances.end()) {
        return it->second;
    }
    return 0.0;
}

bool MultiCurrencyWallet::deposit(const std::string& currency, double amount) {
    if (amount <= 0) return false;
    balances[currency] += amount;
    std::cout << "Deposited " << amount << " " << currency << std::endl;
    return true;
}

bool MultiCurrencyWallet::withdraw(const std::string& currency, double amount) {
    auto it = balances.find(currency);
    if (it != balances.end() && amount > 0 && it->second >= amount) {
        it->second -= amount;
        std::cout << "Withdrew " << amount << " " << currency << std::endl;
        return true;
    }
    return false;
}

std::map<std::string, double> MultiCurrencyWallet::getAllBalances() const {
    return balances;
}

} // namespace VirtualMoney

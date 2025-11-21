/**
 * @file Wallet.cpp
 */

#include "Wallet.h"
#include <iostream>

namespace VirtualMoney {

Wallet::Wallet() : balance(0.0), currency("USD") {}

Wallet::Wallet(const std::string& id, const std::string& userId)
    : id(id), userId(userId), balance(0.0), currency("USD") {}

double Wallet::getBalance() const {
    return balance;
}

bool Wallet::deposit(double amount) {
    if (amount <= 0) return false;
    balance += amount;
    return true;
}

bool Wallet::withdraw(double amount) {
    if (amount <= 0 || amount > balance) return false;
    balance -= amount;
    return true;
}

std::string Wallet::getId() const {
    return id;
}

std::string Wallet::getUserId() const {
    return userId;
}

} // namespace VirtualMoney

#include "Wallet.h"
#include <stdexcept>

Wallet::Wallet(std::string userId, std::string currency, double initialBalance)
    : userId(userId), currency(currency), balance(initialBalance) {
    if (initialBalance < 0) {
        throw std::invalid_argument("Initial balance cannot be negative.");
    }
}

void Wallet::deposit(double amount) {
    if (amount <= 0) {
        throw std::invalid_argument("Deposit amount must be positive.");
    }
    balance += amount;
}

bool Wallet::withdraw(double amount) {
    if (amount <= 0) {
        throw std::invalid_argument("Withdrawal amount must be positive.");
    }
    if (balance >= amount) {
        balance -= amount;
        return true;
    }
    return false;
}

double Wallet::getBalance() const {
    return balance;
}

std::string Wallet::getCurrency() const {
    return currency;
}

std::string Wallet::getUserId() const {
    return userId;
}

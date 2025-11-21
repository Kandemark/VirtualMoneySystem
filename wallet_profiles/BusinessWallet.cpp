/**
 * @file BusinessWallet.cpp
 */

#include "BusinessWallet.h"
#include <iostream>

namespace VirtualMoney {

BusinessWallet::BusinessWallet(const std::string& walletId, const std::string& businessId)
    : walletId(walletId), businessId(businessId), balance(0.0), currency("USD") {}

double BusinessWallet::getBalance() const {
    return balance;
}

bool BusinessWallet::deposit(double amount) {
    if (amount <= 0) return false;
    balance += amount;
    
    Transaction tx;
    tx.type = "deposit";
    tx.amount = amount;
    tx.timestamp = std::time(nullptr);
    transactionHistory.push_back(tx);
    
    return true;
}

bool BusinessWallet::withdraw(double amount) {
    if (amount <= 0 || amount > balance) return false;
    balance -= amount;
    
    Transaction tx;
    tx.type = "withdrawal";
    tx.amount = amount;
    tx.timestamp = std::time(nullptr);
    transactionHistory.push_back(tx);
    
    return true;
}

bool BusinessWallet::processPayroll(const std::vector<std::pair<std::string, double>>& payments) {
    double total = 0.0;
    for (const auto& [employee, amount] : payments) {
        total += amount;
    }
    
    if (total > balance) {
        std::cout << "Insufficient funds for payroll" << std::endl;
        return false;
    }
    
    for (const auto& [employee, amount] : payments) {
        balance -= amount;
        std::cout << "Paid " << employee << ": $" << amount << std::endl;
    }
    
    return true;
}

std::vector<Transaction> BusinessWallet::getTransactionHistory() const {
    return transactionHistory;
}

} // namespace VirtualMoney

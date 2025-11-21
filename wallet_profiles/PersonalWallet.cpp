/**
 * @file PersonalWallet.cpp
 * @brief Personal wallet implementation
 */

#include "PersonalWallet.h"
#include <iostream>

namespace VirtualMoney {

PersonalWallet::PersonalWallet(const std::string& walletId, const std::string& userId)
    : walletId(walletId), userId(userId), balance(0.0), currency("USD") {
    
    // Set personal wallet features
    features["savings_goals"] = true;
    features["budgeting"] = true;
    features["expense_tracking"] = true;
    features["rewards"] = true;
}

double PersonalWallet::getBalance() const {
    return balance;
}

bool PersonalWallet::deposit(double amount) {
    if (amount <= 0) return false;
    
    balance += amount;
    
    Transaction tx;
    tx.type = "deposit";
    tx.amount = amount;
    tx.timestamp = std::time(nullptr);
    tx.description = "Deposit to personal wallet";
    transactionHistory.push_back(tx);
    
    std::cout << "Deposited $" << amount << " to personal wallet " << walletId << std::endl;
    
    return true;
}

bool PersonalWallet::withdraw(double amount) {
    if (amount <= 0 || amount > balance) return false;
    
    balance -= amount;
    
    Transaction tx;
    tx.type = "withdrawal";
    tx.amount = amount;
    tx.timestamp = std::time(nullptr);
    tx.description = "Withdrawal from personal wallet";
    transactionHistory.push_back(tx);
    
    std::cout << "Withdrew $" << amount << " from personal wallet " << walletId << std::endl;
    
    return true;
}

bool PersonalWallet::transfer(const std::string& toWallet, double amount) {
    if (amount <= 0 || amount > balance) return false;
    
    balance -= amount;
    
    Transaction tx;
    tx.type = "transfer";
    tx.amount = amount;
    tx.timestamp = std::time(nullptr);
    tx.description = "Transfer to " + toWallet;
    transactionHistory.push_back(tx);
    
    std::cout << "Transferred $" << amount << " to " << toWallet << std::endl;
    
    return true;
}

bool PersonalWallet::setSavingsGoal(const std::string& goalName, double targetAmount) {
    savingsGoals[goalName] = targetAmount;
    
    std::cout << "Savings goal set: " << goalName << " ($" << targetAmount << ")" << std::endl;
    
    return true;
}

std::vector<Transaction> PersonalWallet::getTransactionHistory() const {
    return transactionHistory;
}

std::map<std::string, double> PersonalWallet::getSavingsGoals() const {
    return savingsGoals;
}

} // namespace VirtualMoney

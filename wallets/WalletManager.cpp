/**
 * @file WalletManager.cpp
 */

#include "WalletManager.h"
#include <iostream>

namespace VirtualMoney {

WalletManager::WalletManager() {}

std::string WalletManager::createWallet(const std::string& userId, const std::string& currency) {
    Wallet wallet;
    wallet.id = "WALLET_" + std::to_string(wallets.size() + 1);
    wallet.userId = userId;
    wallet.balance = 0.0;
    wallet.currency = currency;
    
    wallets[wallet.id] = wallet;
    
    std::cout << "Wallet created: " << wallet.id << " for user " << userId << std::endl;
    
    return wallet.id;
}

double WalletManager::getBalance(const std::string& walletId) {
    auto it = wallets.find(walletId);
    if (it != wallets.end()) {
        return it->second.balance;
    }
    return 0.0;
}

bool WalletManager::deposit(const std::string& walletId, double amount) {
    auto it = wallets.find(walletId);
    if (it != wallets.end() && amount > 0) {
        it->second.balance += amount;
        std::cout << "Deposited $" << amount << " to " << walletId << std::endl;
        return true;
    }
    return false;
}

bool WalletManager::withdraw(const std::string& walletId, double amount) {
    auto it = wallets.find(walletId);
    if (it != wallets.end() && amount > 0 && it->second.balance >= amount) {
        it->second.balance -= amount;
        std::cout << "Withdrew $" << amount << " from " << walletId << std::endl;
        return true;
    }
    return false;
}

} // namespace VirtualMoney

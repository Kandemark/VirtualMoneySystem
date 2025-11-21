/**
 * @file StockWallet.cpp
 */

#include "StockWallet.h"
#include <iostream>

StockWallet::StockWallet(const std::string& walletId, const std::string& userId)
    : walletId(walletId), userId(userId), cashBalance(0.0) {}

bool StockWallet::buyStock(const std::string& symbol, int shares, double pricePerShare) {
    double totalCost = shares * pricePerShare;
    
    if (totalCost > cashBalance) {
        std::cout << "Insufficient funds to buy stock" << std::endl;
        return false;
    }
    
    cashBalance -= totalCost;
    holdings[symbol] += shares;
    
    std::cout << "Bought " << shares << " shares of " << symbol 
              << " @ $" << pricePerShare << std::endl;
    
    return true;
}

bool StockWallet::sellStock(const std::string& symbol, int shares, double pricePerShare) {
    auto it = holdings.find(symbol);
    if (it == holdings.end() || it->second < shares) {
        std::cout << "Insufficient shares to sell" << std::endl;
        return false;
    }
    
    it->second -= shares;
    cashBalance += shares * pricePerShare;
    
    std::cout << "Sold " << shares << " shares of " << symbol 
              << " @ $" << pricePerShare << std::endl;
    
    return true;
}

int StockWallet::getShares(const std::string& symbol) const {
    auto it = holdings.find(symbol);
    if (it != holdings.end()) {
        return it->second;
    }
    return 0;
}

double StockWallet::getCashBalance() const {
    return cashBalance;
}

void StockWallet::depositCash(double amount) {
    cashBalance += amount;
}

std::map<std::string, int> StockWallet::getAllHoldings() const {
    return holdings;
}

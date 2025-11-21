/**
 * @file Wallet.h
 * @brief Core wallet implementation
 */

#ifndef WALLET_H
#define WALLET_H

#include <string>
#include <map>

class Wallet {
public:
    Wallet(const std::string& walletId, const std::string& userId);
    
    double getBalance(const std::string& currency = "USD");
    void deposit(double amount, const std::string& currency = "USD");
    bool withdraw(double amount, const std::string& currency = "USD");
    
    std::string getWalletId() const;
    std::string getUserId() const;
    
    std::map<std::string, double> getAllBalances();
    void freeze();
    void unfreeze();
    bool isFrozen();

private:
    std::string walletId;
    std::string userId;
    std::map<std::string, double> balances;
    bool frozen;
};

#endif

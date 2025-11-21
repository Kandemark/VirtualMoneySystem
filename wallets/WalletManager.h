/**
 * @file WalletManager.h
 * @brief Wallet management system
 */

#ifndef WALLET_MANAGER_H
#define WALLET_MANAGER_H

#include <string>
#include <vector>
#include <map>

class WalletManager {
public:
    std::string createWallet(const std::string& userId, const std::string& walletType = "personal");
    bool deleteWallet(const std::string& walletId);
    
    std::vector<std::string> getUserWallets(const std::string& userId);
    double getWalletBalance(const std::string& walletId, const std::string& currency = "USD");
    
    bool transferBetweenWallets(const std::string& fromWalletId, const std::string& toWalletId, 
                                double amount, const std::string& currency = "USD");
    
    void freezeWallet(const std::string& walletId);
    void unfreezeWallet(const std::string& walletId);

private:
    std::map<std::string, std::string> walletOwners;
};

#endif

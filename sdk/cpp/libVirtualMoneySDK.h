/**
 * @file libVirtualMoneySDK.h
 * @brief C++ SDK library interface
 */

#ifndef LIB_VIRTUAL_MONEY_SDK_H
#define LIB_VIRTUAL_MONEY_SDK_H

#include <string>

namespace VirtualMoneySDK {

class SDK {
public:
    void initialize(const std::string& apiKey, const std::string& endpoint);
    std::string createWallet(const std::string& userId);
    std::string makeTransaction(const std::string& fromWallet, const std::string& toWallet, double amount);
    double getBalance(const std::string& walletId);
};

}

#endif

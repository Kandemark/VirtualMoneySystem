/**
 * @file WalletEndpoints.cpp (v1)
 */

#include "WalletEndpoints.h"
#include <iostream>

namespace VirtualMoney {
namespace API {
namespace V1 {

std::string createWallet(const std::string& userId, const std::string& currency) {
    std::cout << "API v1: Create wallet for " << userId << std::endl;
    return "{\"walletId\": \"WALLET_123\", \"balance\": 0.0}";
}

std::string getBalance(const std::string& walletId) {
    std::cout << "API v1: Get balance - " << walletId << std::endl;
    return "{\"balance\": 1000.0, \"currency\": \"USD\"}";
}

bool deposit(const std::string& walletId, double amount) {
    std::cout << "API v1: Deposit $" << amount << " to " << walletId << std::endl;
    return true;
}

bool withdraw(const std::string& walletId, double amount) {
    std::cout << "API v1: Withdraw $" << amount << " from " << walletId << std::endl;
    return true;
}

} // namespace V1
} // namespace API
} // namespace VirtualMoney

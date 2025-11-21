/**
 * @file CppWrapper.cpp - C++ SDK wrapper
 */

#include "CppWrapper.h"
#include <iostream>

namespace VirtualMoney {
namespace SDK {

CppWrapper::CppWrapper(const std::string& apiKey) : apiKey(apiKey) {
    std::cout << "SDK initialized" << std::endl;
}

std::string CppWrapper::createWallet(const std::string& userId) {
    return "WALLET_" + userId;
}

bool CppWrapper::transfer(const std::string& from, const std::string& to, double amount) {
    std::cout << "Transfer: $" << amount << " from " << from << " to " << to << std::endl;
    return true;
}

double CppWrapper::getBalance(const std::string& walletId) {
    return 1000.0;
}

} // namespace SDK
} // namespace VirtualMoney

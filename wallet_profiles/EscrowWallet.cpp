/**
 * @file EscrowWallet.cpp
 */

#include "EscrowWallet.h"
#include <iostream>

namespace VirtualMoney {

EscrowWallet::EscrowWallet(const std::string& walletId, const std::string& buyerId, const std::string& sellerId)
    : walletId(walletId), buyerId(buyerId), sellerId(sellerId), balance(0.0), released(false) {}

bool EscrowWallet::depositFunds(double amount) {
    if (amount <= 0 || released) return false;
    balance += amount;
    std::cout << "Funds deposited to escrow: $" << amount << std::endl;
    return true;
}

bool EscrowWallet::releaseFunds() {
    if (released || balance == 0) return false;
    
    released = true;
    std::cout << "Escrow funds released to seller: $" << balance << std::endl;
    balance = 0.0;
    
    return true;
}

bool EscrowWallet::refundFunds() {
    if (released || balance == 0) return false;
    
    std::cout << "Escrow funds refunded to buyer: $" << balance << std::endl;
    balance = 0.0;
    
    return true;
}

double EscrowWallet::getBalance() const {
    return balance;
}

bool EscrowWallet::isReleased() const {
    return released;
}

} // namespace VirtualMoney

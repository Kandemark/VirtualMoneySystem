/**
 * @file InterestPayout.cpp
 */

#include "InterestPayout.h"
#include <iostream>

InterestPayout::InterestPayout() : annualRate(0.05) {}

void InterestPayout::processPayouts() {
    std::cout << "Processing interest payouts..." << std::endl;
    
    for (const auto& [userId, balance] : balances) {
        double interest = calculateInterest(balance);
        balances[userId] += interest;
        std::cout << "Paid interest to " << userId << ": $" << interest << std::endl;
    }
}

double InterestPayout::calculateInterest(double balance) const {
    // Monthly interest = annual rate / 12
    return balance * (annualRate / 12.0);
}

void InterestPayout::setInterestRate(double rate) {
    annualRate = rate;
    std::cout << "Interest rate set to: " << (rate * 100) << "%" << std::endl;
}

void InterestPayout::addAccount(const std::string& userId, double balance) {
    balances[userId] = balance;
}

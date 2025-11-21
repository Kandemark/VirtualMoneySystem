/**
 * @file LoanPlugin.cpp - Loan management plugin
 */

#include "LoanPlugin.h"
#include <iostream>

namespace VirtualMoney {
namespace Plugins {

LoanPlugin::LoanPlugin() {}

std::string LoanPlugin::createLoan(const std::string& userId, double amount, double interestRate, int termMonths) {
    std::string loanId = "LOAN_" + std::to_string(loans.size() + 1);
    
    Loan loan;
    loan.loanId = loanId;
    loan.userId = userId;
    loan.principal = amount;
    loan.interestRate = interestRate;
    loan.termMonths = termMonths;
    loan.remainingBalance = amount;
    loan.active = true;
    
    loans[loanId] = loan;
    
    std::cout << "Loan created: " << loanId << " for $" << amount << std::endl;
    
    return loanId;
}

bool LoanPlugin::makePayment(const std::string& loanId, double amount) {
    auto it = loans.find(loanId);
    if (it != loans.end() && it->second.active) {
        it->second.remainingBalance -= amount;
        std::cout << "Payment of $" << amount << " applied to loan " << loanId << std::endl;
        
        if (it->second.remainingBalance <= 0) {
            it->second.active = false;
            std::cout << "Loan " << loanId << " paid off!" << std::endl;
        }
        
        return true;
    }
    return false;
}

double LoanPlugin::getRemainingBalance(const std::string& loanId) const {
    auto it = loans.find(loanId);
    if (it != loans.end()) {
        return it->second.remainingBalance;
    }
    return 0.0;
}

} // namespace Plugins
} // namespace VirtualMoney

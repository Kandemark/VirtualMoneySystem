/**
 * @file MicroLoanPlugin.cpp
 */

#include "MicroLoanPlugin.h"
#include <iostream>

namespace VirtualMoney {
namespace Plugins {

MicroLoanPlugin::MicroLoanPlugin() {}

std::string MicroLoanPlugin::createMicroLoan(const std::string& userId, double amount) {
    if (amount > 1000.0) {
        std::cout << "Amount exceeds micro-loan limit" << std::endl;
        return "";
    }
    
    std::string loanId = "MICROLOAN_" + std::to_string(microLoans.size() + 1);
    
    MicroLoan loan;
    loan.loanId = loanId;
    loan.userId = userId;
    loan.amount = amount;
    loan.interestRate = 0.05; // 5% for micro-loans
    loan.dueDate = std::time(nullptr) + (30 * 86400); // 30 days
    loan.repaid = false;
    
    microLoans[loanId] = loan;
    
    std::cout << "Micro-loan created: " << loanId << " for $" << amount << std::endl;
    
    return loanId;
}

bool MicroLoanPlugin::repayLoan(const std::string& loanId) {
    auto it = microLoans.find(loanId);
    if (it != microLoans.end()) {
        it->second.repaid = true;
        std::cout << "Micro-loan repaid: " << loanId << std::endl;
        return true;
    }
    return false;
}

std::vector<MicroLoan> MicroLoanPlugin::getActiveLoans(const std::string& userId) const {
    std::vector<MicroLoan> active;
    for (const auto& [id, loan] : microLoans) {
        if (loan.userId == userId && !loan.repaid) {
            active.push_back(loan);
        }
    }
    return active;
}

} // namespace Plugins
} // namespace VirtualMoney

#include "LoanManager.h"
#include <cmath>

std::string LoanManager::createLoan(const std::string& userId, double amount, double interestRate, int termMonths) {
    Loan loan;
    loan.loanId = "LOAN_" + std::to_string(loans.size() + 1);
    loan.userId = userId;
    loan.principal = amount;
    loan.interestRate = interestRate;
    loan.termMonths = termMonths;
    loan.monthlyPayment = calculateMonthlyPayment(amount, interestRate, termMonths);
    loan.remainingBalance = amount;
    loan.startDate = std::chrono::system_clock::now();
    loan.isActive = false;
    
    loans[loan.loanId] = loan;
    return loan.loanId;
}

bool LoanManager::approveLoan(const std::string& loanId) {
    auto it = loans.find(loanId);
    if (it != loans.end()) {
        it->second.isActive = true;
        return true;
    }
    return false;
}

void LoanManager::recordPayment(const std::string& loanId, double amount) {
    auto it = loans.find(loanId);
    if (it != loans.end()) {
        it->second.remainingBalance -= amount;
    }
}

Loan LoanManager::getLoan(const std::string& loanId) {
    return loans.at(loanId);
}

double LoanManager::calculateMonthlyPayment(double principal, double interestRate, int termMonths) {
    double monthlyRate = interestRate / 12.0 / 100.0;
    return principal * (monthlyRate * std::pow(1 + monthlyRate, termMonths)) / 
           (std::pow(1 + monthlyRate, termMonths) - 1);
}

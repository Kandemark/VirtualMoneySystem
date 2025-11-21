/**
 * @file LoanManager.h
 * @brief Personal and business loan management
 */

#ifndef LOAN_MANAGER_H
#define LOAN_MANAGER_H

#include <string>
#include <map>
#include <chrono>

struct Loan {
    std::string loanId;
    std::string userId;
    double principal;
    double interestRate;
    int termMonths;
    double monthlyPayment;
    double remainingBalance;
    std::chrono::system_clock::time_point startDate;
    bool isActive;
};

class LoanManager {
public:
    std::string createLoan(const std::string& userId, double amount, double interestRate, int termMonths);
    bool approveLoan(const std::string& loanId);
    void recordPayment(const std::string& loanId, double amount);
    Loan getLoan(const std::string& loanId);
    double calculateMonthlyPayment(double principal, double interestRate, int termMonths);
private:
    std::map<std::string, Loan> loans;
};

#endif

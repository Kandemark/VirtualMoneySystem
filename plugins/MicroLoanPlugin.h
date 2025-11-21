/**
 * @file MicroLoanPlugin.h
 * @brief Micro-loan plugin
 */

#ifndef MICRO_LOAN_PLUGIN_H
#define MICRO_LOAN_PLUGIN_H

#include <string>

class MicroLoanPlugin {
public:
    void initialize();
    std::string applyForLoan(const std::string& userId, double amount);
    std::string getLoanStatus(const std::string& loanId);
    void repayLoan(const std::string& loanId, double amount);
};

#endif

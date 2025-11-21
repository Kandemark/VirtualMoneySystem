/**
 * @file LoanPlugin.h
 * @brief Loan marketplace plugin
 */

#ifndef LOAN_PLUGIN_H
#define LOAN_PLUGIN_H

#include <string>

class LoanPlugin {
public:
    void initialize();
    std::string applyForLoan(const std::string& userId, double amount, int termMonths);
    std::string getLoanOffers(const std::string& userId);
    void acceptOffer(const std::string& offerId);
};

#endif

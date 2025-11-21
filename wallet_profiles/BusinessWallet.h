/**
 * @file BusinessWallet.h
 * @brief Business wallet profile
 */

#ifndef BUSINESS_WALLET_H
#define BUSINESS_WALLET_H

#include <string>
#include <vector>

class BusinessWallet {
public:
    BusinessWallet(const std::string& businessId);
    void addAuthorizedUser(const std::string& userId);
    void removeAuthorizedUser(const std::string& userId);
    std::vector<std::string> getAuthorizedUsers();
    void setTransactionApprovalRequired(bool required);
    void setMonthlyBudget(double budget);

private:
    std::string businessId;
    std::vector<std::string> authorizedUsers;
    bool approvalRequired;
    double monthlyBudget;
};

#endif

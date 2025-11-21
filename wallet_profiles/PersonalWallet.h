/**
 * @file PersonalWallet.h
 * @brief Personal wallet profile
 */

#ifndef PERSONAL_WALLET_H
#define PERSONAL_WALLET_H

#include <string>

class PersonalWallet {
public:
    PersonalWallet(const std::string& userId);
    void setSpendingLimit(double limit);
    double getSpendingLimit();
    void enableSavingsMode(bool enabled);
    bool isSavingsModeEnabled();

private:
    std::string userId;
    double spendingLimit;
    bool savingsMode;
};

#endif

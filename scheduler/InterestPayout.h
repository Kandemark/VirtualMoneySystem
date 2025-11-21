/**
 * @file InterestPayout.h
 * @brief Scheduled interest payouts
 */

#ifndef INTEREST_PAYOUT_H
#define INTEREST_PAYOUT_H

#include <string>

class InterestPayout {
public:
    void calculateInterest(const std::string& userId);
    void payoutInterest(const std::string& userId);
};

#endif

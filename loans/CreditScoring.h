/**
 * @file CreditScoring.h
 * @brief Credit score calculation and assessment
 */

#ifndef CREDIT_SCORING_H
#define CREDIT_SCORING_H

#include <string>

class CreditScoring {
public:
    int calculateCreditScore(const std::string& userId);
    bool isEligibleForLoan(const std::string& userId, double amount);
    std::string getCreditRating(int score);
private:
    int baseScore = 650;
};

#endif

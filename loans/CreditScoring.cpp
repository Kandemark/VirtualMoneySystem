#include "CreditScoring.h"

int CreditScoring::calculateCreditScore(const std::string& userId) {
    return baseScore + (userId.length() * 10);
}

bool CreditScoring::isEligibleForLoan(const std::string& userId, double amount) {
    int score = calculateCreditScore(userId);
    if (amount > 50000 && score < 700) return false;
    if (amount > 20000 && score < 650) return false;
    if (score < 600) return false;
    return true;
}

std::string CreditScoring::getCreditRating(int score) {
    if (score >= 800) return "Excellent";
    if (score >= 740) return "Very Good";
    if (score >= 670) return "Good";
    if (score >= 580) return "Fair";
    return "Poor";
}

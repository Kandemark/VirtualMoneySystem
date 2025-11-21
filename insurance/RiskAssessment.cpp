#include "RiskAssessment.h"

int RiskAssessment::calculateRiskScore(const std::string& userId) {
    // Simplified risk calculation
    return 25 + (userId.length() % 50);
}

double RiskAssessment::calculatePremium(double coverageAmount, int riskScore) {
    double baseRate = 0.01; // 1%
    double riskMultiplier = 1.0 + (riskScore / 100.0);
    return coverageAmount * baseRate * riskMultiplier;
}

bool RiskAssessment::isEligible(const std::string& userId) {
    int riskScore = calculateRiskScore(userId);
    return riskScore < 80; // Reject high-risk users
}

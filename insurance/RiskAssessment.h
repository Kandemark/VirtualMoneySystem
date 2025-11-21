/**
 * @file RiskAssessment.h
 * @brief Insurance risk assessment
 */

#ifndef RISK_ASSESSMENT_H
#define RISK_ASSESSMENT_H

#include <string>

/**
 * @brief Assesses insurance risk
 */
class RiskAssessment {
public:
    /**
     * @brief Calculate risk score for user
     * @param userId User identifier
     * @return Risk score (0-100, higher = riskier)
     */
    int calculateRiskScore(const std::string& userId);
    
    /**
     * @brief Determine premium based on risk
     * @param coverageAmount Coverage amount
     * @param riskScore Risk score
     * @return Premium amount
     */
    double calculatePremium(double coverageAmount, int riskScore);
    
    /**
     * @brief Check if user is eligible for insurance
     * @param userId User identifier
     * @return true if eligible
     */
    bool isEligible(const std::string& userId);
};

#endif

/**
 * @file InsuranceManager.h
 * @brief Insurance policy management
 */

#ifndef INSURANCE_MANAGER_H
#define INSURANCE_MANAGER_H

#include <string>
#include <map>

/**
 * @brief Insurance policy
 */
struct InsurancePolicy {
    std::string policyId;
    std::string userId;
    std::string type;          ///< Type: fraud, transaction, account
    double coverageAmount;
    double premium;
    bool isActive;
};

/**
 * @brief Manages insurance policies
 */
class InsuranceManager {
public:
    /**
     * @brief Create insurance policy
     * @param userId User identifier
     * @param type Policy type
     * @param coverageAmount Coverage amount
     * @return Policy ID
     */
    std::string createPolicy(const std::string& userId, const std::string& type, double coverageAmount);
    
    /**
     * @brief File insurance claim
     * @param policyId Policy identifier
     * @param claimAmount Claim amount
     * @param reason Claim reason
     * @return Claim ID
     */
    std::string fileClaim(const std::string& policyId, double claimAmount, const std::string& reason);
    
    /**
     * @brief Get policy details
     * @param policyId Policy identifier
     * @return Policy information
     */
    InsurancePolicy getPolicy(const std::string& policyId);

private:
    std::map<std::string, InsurancePolicy> policies;
};

#endif

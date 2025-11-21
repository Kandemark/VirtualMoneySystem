#include "InsuranceManager.h"

std::string InsuranceManager::createPolicy(const std::string& userId, const std::string& type, double coverageAmount) {
    InsurancePolicy policy;
    policy.policyId = "POL_" + std::to_string(policies.size() + 1);
    policy.userId = userId;
    policy.type = type;
    policy.coverageAmount = coverageAmount;
    policy.premium = coverageAmount * 0.01; // 1% of coverage
    policy.isActive = true;
    
    policies[policy.policyId] = policy;
    return policy.policyId;
}

std::string InsuranceManager::fileClaim(const std::string& policyId, double claimAmount, const std::string& reason) {
    return "CLAIM_" + policyId + "_" + std::to_string(rand() % 10000);
}

InsurancePolicy InsuranceManager::getPolicy(const std::string& policyId) {
    return policies.at(policyId);
}

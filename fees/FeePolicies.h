/**
 * @file FeePolicies.h
 * @brief Fee policy management
 */

#ifndef FEE_POLICIES_H
#define FEE_POLICIES_H

#include <string>

class FeePolicies {
public:
    void createPolicy(const std::string& policyId, const std::string& policyData);
    std::string getPolicy(const std::string& policyId);
    void updatePolicy(const std::string& policyId, const std::string& policyData);
    void deletePolicy(const std::string& policyId);
};

#endif

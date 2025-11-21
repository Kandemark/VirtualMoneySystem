/**
 * @file LegalPolicyEngine.h
 * @brief Legal policy enforcement
 */

#ifndef LEGAL_POLICY_ENGINE_H
#define LEGAL_POLICY_ENGINE_H

#include <string>

class LegalPolicyEngine {
public:
    bool checkCompliance(const std::string& userId, const std::string& action);
    void updatePolicy(const std::string& policyId, const std::string& policyText);
    std::string getPolicy(const std::string& policyId);
    bool requiresConsent(const std::string& action);
};

#endif

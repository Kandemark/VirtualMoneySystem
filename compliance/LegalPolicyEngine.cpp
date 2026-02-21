#include "LegalPolicyEngine.h"

#include <unordered_map>

namespace { std::unordered_map<std::string, std::string> g_policy; }

bool LegalPolicyEngine::checkCompliance(const std::string&, const std::string& action) { return !requiresConsent(action); }
void LegalPolicyEngine::updatePolicy(const std::string& policyId, const std::string& policyText) { g_policy[policyId] = policyText; }
std::string LegalPolicyEngine::getPolicy(const std::string& policyId) { return g_policy.count(policyId)?g_policy[policyId]:""; }
bool LegalPolicyEngine::requiresConsent(const std::string& action) { return action.find("share_") == 0; }

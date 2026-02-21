#include "InsurancePlugin.h"

#include <unordered_map>

namespace { std::unordered_map<std::string, std::string> g_policy; }

void InsurancePlugin::initialize() { g_policy.clear(); }
std::string InsurancePlugin::purchaseInsurance(const std::string& userId, const std::string& insuranceType) {
    const std::string id = "policy_" + std::to_string(std::hash<std::string>{}(userId + insuranceType));
    g_policy[id] = "ACTIVE:" + insuranceType;
    return id;
}
std::string InsurancePlugin::getInsuranceStatus(const std::string& policyId) { return g_policy.count(policyId)?g_policy[policyId]:"NOT_FOUND"; }
void InsurancePlugin::fileClaim(const std::string& policyId, const std::string& claimDetails) { if (g_policy.count(policyId)) g_policy[policyId] += "|CLAIM:" + claimDetails; }

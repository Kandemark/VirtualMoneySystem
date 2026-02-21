
#include "FeePolicies.h"

#include <mutex>
#include <unordered_map>

namespace {
std::mutex g_policyMutex;
std::unordered_map<std::string, std::string> g_policies;
} // namespace

void FeePolicies::createPolicy(const std::string &policyId,
                               const std::string &policyData) {
  std::lock_guard<std::mutex> lock(g_policyMutex);
  g_policies.emplace(policyId, policyData);
}

std::string FeePolicies::getPolicy(const std::string &policyId) {
  std::lock_guard<std::mutex> lock(g_policyMutex);
  auto it = g_policies.find(policyId);
  if (it == g_policies.end()) {
    return "";
  }
  return it->second;
}

void FeePolicies::updatePolicy(const std::string &policyId,
                               const std::string &policyData) {
  std::lock_guard<std::mutex> lock(g_policyMutex);
  g_policies[policyId] = policyData;
}

void FeePolicies::deletePolicy(const std::string &policyId) {
  std::lock_guard<std::mutex> lock(g_policyMutex);
  g_policies.erase(policyId);
}

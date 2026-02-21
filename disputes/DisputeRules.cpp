#include "DisputeRules.h"

#include <unordered_map>

namespace { std::unordered_map<std::string, std::pair<std::string, std::string>> g_rules; }

void DisputeRules::addRule(const std::string& ruleId, const std::string& condition, const std::string& action) { g_rules[ruleId] = {condition, action}; }

bool DisputeRules::evaluateRule(const std::string& ruleId, const std::string& disputeData) {
    auto it = g_rules.find(ruleId);
    return it != g_rules.end() && disputeData.find(it->second.first) != std::string::npos;
}

std::string DisputeRules::getRecommendedAction(const std::string& disputeId) {
    for (const auto& [id, rule] : g_rules) if (disputeId.find(rule.first) != std::string::npos) return rule.second;
    return "manual_review";
}

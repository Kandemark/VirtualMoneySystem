#include "AutoSave.h"
#include <cmath>

std::string AutoSave::createRule(const std::string& userId, const std::string& type, double amount) {
    AutoSaveRule rule;
    rule.ruleId = "RULE_" + std::to_string(rules.size() + 1);
    rule.userId = userId;
    rule.type = type;
    rule.amount = amount;
    rule.isActive = true;
    
    rules[rule.ruleId] = rule;
    return rule.ruleId;
}

double AutoSave::processTransaction(const std::string& userId, double transactionAmount) {
    double savedAmount = 0.0;
    
    for (const auto& [ruleId, rule] : rules) {
        if (rule.userId == userId && rule.isActive) {
            if (rule.type == "round_up") {
                savedAmount += std::ceil(transactionAmount) - transactionAmount;
            } else if (rule.type == "percentage") {
                savedAmount += transactionAmount * (rule.amount / 100.0);
            } else if (rule.type == "fixed") {
                savedAmount += rule.amount;
            }
        }
    }
    
    return savedAmount;
}

void AutoSave::setRuleStatus(const std::string& ruleId, bool enabled) {
    auto it = rules.find(ruleId);
    if (it != rules.end()) {
        it->second.isActive = enabled;
    }
}

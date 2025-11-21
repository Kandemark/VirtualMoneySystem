/**
 * @file RulesEngine.cpp
 */

#include "RulesEngine.h"
#include <iostream>

RulesEngine::RulesEngine() {}

void RulesEngine::addRule(const std::string& ruleId, const std::string& condition, const std::string& action) {
    Rule rule;
    rule.ruleId = ruleId;
    rule.condition = condition;
    rule.action = action;
    rule.enabled = true;
    
    rules[ruleId] = rule;
    std::cout << "Rule added: " << ruleId << std::endl;
}

bool RulesEngine::evaluateRules(const std::map<std::string, std::string>& context) {
    for (const auto& [id, rule] : rules) {
        if (rule.enabled && evaluateCondition(rule.condition, context)) {
            executeAction(rule.action);
            return true;
        }
    }
    return false;
}

bool RulesEngine::evaluateCondition(const std::string& condition, const std::map<std::string, std::string>& context) {
    // Simplified condition evaluation
    return true;
}

void RulesEngine::executeAction(const std::string& action) {
    std::cout << "Executing action: " << action << std::endl;
}

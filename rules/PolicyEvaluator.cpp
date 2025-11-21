/**
 * @file PolicyEvaluator.cpp
 */

#include "PolicyEvaluator.h"
#include <iostream>
#include <algorithm>

bool PolicyEvaluator::evaluatePolicy(const std::string& policyId, const std::map<std::string, std::string>& data) {
    auto it = policies.find(policyId);
    if (it == policies.end()) {
        return false;
    }
    
    std::string expression = it->second;
    
    // Simple policy evaluation (in production, use expression parser)
    if (expression.find("amount") != std::string::npos) {
        auto amountIt = data.find("amount");
        if (amountIt != data.end()) {
            double amount = std::stod(amountIt->second);
            if (expression.find(">") != std::string::npos) {
                return amount > 1000.0;
            }
        }
    }
    
    return true;
}

void PolicyEvaluator::registerPolicy(const std::string& policyId, const std::string& policyExpression) {
    policies[policyId] = policyExpression;
    std::cout << "Policy registered: " << policyId << std::endl;
}

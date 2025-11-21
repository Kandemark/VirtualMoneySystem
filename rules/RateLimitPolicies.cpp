/**
 * @file RateLimitPolicies.cpp
 */

#include "RateLimitPolicies.h"
#include <iostream>

RateLimitPolicies::RateLimitPolicies() {
    policies["default"] = {100, 60}; // 100 requests per 60 seconds
    policies["premium"] = {1000, 60};
    policies["enterprise"] = {10000, 60};
}

bool RateLimitPolicies::checkLimit(const std::string& userId, const std::string& policyName) {
    auto it = policies.find(policyName);
    if (it == policies.end()) {
        return false;
    }
    
    auto& policy = it->second;
    auto& usage = userUsage[userId];
    
    std::time_t now = std::time(nullptr);
    
    // Reset if window expired
    if (now - usage.windowStart >= policy.windowSeconds) {
        usage.count = 0;
        usage.windowStart = now;
    }
    
    if (usage.count >= policy.maxRequests) {
        std::cout << "Rate limit exceeded for " << userId << std::endl;
        return false;
    }
    
    usage.count++;
    return true;
}

void RateLimitPolicies::setPolicy(const std::string& policyName, int maxRequests, int windowSeconds) {
    policies[policyName] = {maxRequests, windowSeconds};
    std::cout << "Rate limit policy set: " << policyName << std::endl;
}

/**
 * @file TierAccessControl.cpp
 */

#include "TierAccessControl.h"
#include <iostream>

TierAccessControl::TierAccessControl() {
    // Initialize tier limits
    tierLimits["free"] = {10, 1, 100};
    tierLimits["starter"] = {100, 5, 1000};
    tierLimits["professional"] = {1000, -1, 10000};
    tierLimits["enterprise"] = {-1, -1, -1};
}

bool TierAccessControl::checkLimit(const std::string& userId, const std::string& limitType) {
    auto tierIt = userTiers.find(userId);
    if (tierIt == userTiers.end()) {
        return false;
    }
    
    auto limitsIt = tierLimits.find(tierIt->second);
    if (limitsIt == tierLimits.end()) {
        return false;
    }
    
    // Check specific limit (-1 means unlimited)
    if (limitType == "transactions") {
        return limitsIt->second.maxTransactions == -1 || 
               userUsage[userId].transactions < limitsIt->second.maxTransactions;
    }
    
    return true;
}

void TierAccessControl::recordUsage(const std::string& userId, const std::string& usageType) {
    if (usageType == "transaction") {
        userUsage[userId].transactions++;
    }
}

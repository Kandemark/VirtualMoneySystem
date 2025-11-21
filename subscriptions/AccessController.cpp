/**
 * @file AccessController.cpp
 */

#include "AccessController.h"
#include <iostream>

AccessController::AccessController() {}

bool AccessController::hasAccess(const std::string& userId, const std::string& feature) {
    auto it = userTiers.find(userId);
    if (it == userTiers.end()) {
        return false;
    }
    
    std::string tier = it->second;
    auto tierIt = tierFeatures.find(tier);
    
    if (tierIt != tierFeatures.end()) {
        return tierIt->second.find(feature) != tierIt->second.end();
    }
    
    return false;
}

void AccessController::setUserTier(const std::string& userId, const std::string& tier) {
    userTiers[userId] = tier;
    std::cout << "User " << userId << " set to tier: " << tier << std::endl;
}

void AccessController::addFeatureToTier(const std::string& tier, const std::string& feature) {
    tierFeatures[tier].insert(feature);
    std::cout << "Feature " << feature << " added to tier: " << tier << std::endl;
}

#include "TierAccessControl.h"

TierAccessControl::TierAccessControl() {
    tierLimits[UserTier::BASIC] = 1000.0;
    tierLimits[UserTier::SILVER] = 10000.0;
    tierLimits[UserTier::GOLD] = 50000.0;
    tierLimits[UserTier::PLATINUM] = 1000000.0;
}

void TierAccessControl::setUserTier(const std::string& userId, UserTier tier) {
    userTiers[userId] = tier;
}

UserTier TierAccessControl::getUserTier(const std::string& userId) const {
    auto it = userTiers.find(userId);
    return (it != userTiers.end()) ? it->second : UserTier::BASIC;
}

double TierAccessControl::getTransactionLimit(const std::string& userId) const {
    return tierLimits.at(getUserTier(userId));
}

bool TierAccessControl::canAccessFeature(const std::string& userId, const std::string& feature) const {
    auto tier = getUserTier(userId);
    if (feature == "crypto" && tier >= UserTier::GOLD) return true;
    if (feature == "international" && tier >= UserTier::SILVER) return true;
    return true;
}

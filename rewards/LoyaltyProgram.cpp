#include "LoyaltyProgram.h"

LoyaltyTier LoyaltyProgram::getTier(const std::string& userId) {
    auto it = userTiers.find(userId);
    return (it != userTiers.end()) ? it->second : LoyaltyTier::BRONZE;
}

void LoyaltyProgram::updateTier(const std::string& userId, int totalSpend) {
    if (totalSpend >= 100000) {
        userTiers[userId] = LoyaltyTier::DIAMOND;
    } else if (totalSpend >= 50000) {
        userTiers[userId] = LoyaltyTier::PLATINUM;
    } else if (totalSpend >= 20000) {
        userTiers[userId] = LoyaltyTier::GOLD;
    } else if (totalSpend >= 5000) {
        userTiers[userId] = LoyaltyTier::SILVER;
    } else {
        userTiers[userId] = LoyaltyTier::BRONZE;
    }
}

double LoyaltyProgram::getTierMultiplier(LoyaltyTier tier) {
    switch (tier) {
        case LoyaltyTier::DIAMOND: return 3.0;
        case LoyaltyTier::PLATINUM: return 2.5;
        case LoyaltyTier::GOLD: return 2.0;
        case LoyaltyTier::SILVER: return 1.5;
        case LoyaltyTier::BRONZE: return 1.0;
    }
    return 1.0;
}

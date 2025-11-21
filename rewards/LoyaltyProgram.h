#ifndef LOYALTY_PROGRAM_H
#define LOYALTY_PROGRAM_H
#include <string>
#include <map>

enum class LoyaltyTier { BRONZE, SILVER, GOLD, PLATINUM, DIAMOND };

class LoyaltyProgram {
public:
    LoyaltyTier getTier(const std::string& userId);
    void updateTier(const std::string& userId, int totalSpend);
    double getTierMultiplier(LoyaltyTier tier);
private:
    std::map<std::string, LoyaltyTier> userTiers;
};

#endif

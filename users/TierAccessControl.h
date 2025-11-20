#ifndef TIER_ACCESS_CONTROL_H
#define TIER_ACCESS_CONTROL_H
#include <string>
#include <map>

enum class UserTier { BASIC, SILVER, GOLD, PLATINUM };

class TierAccessControl {
public:
    TierAccessControl();
    void setUserTier(const std::string& userId, UserTier tier);
    UserTier getUserTier(const std::string& userId) const;
    double getTransactionLimit(const std::string& userId) const;
    bool canAccessFeature(const std::string& userId, const std::string& feature) const;

private:
    std::map<std::string, UserTier> userTiers;
    std::map<UserTier, double> tierLimits;
};

#endif

/**
 * @file TierAccessControl.h
 * @brief Tier-based access control
 */

#ifndef TIER_ACCESS_CONTROL_H
#define TIER_ACCESS_CONTROL_H

#include <string>

class TierAccessControl {
public:
    void setUserTier(const std::string& userId, const std::string& tier);
    std::string getUserTier(const std::string& userId);
    bool canAccessFeature(const std::string& userId, const std::string& feature);
};

#endif

/**
 * @file LoyaltyPointsPlugin.h
 * @brief Loyalty points plugin
 */

#ifndef LOYALTY_POINTS_PLUGIN_H
#define LOYALTY_POINTS_PLUGIN_H

#include <string>

class LoyaltyPointsPlugin {
public:
    void initialize();
    void awardPoints(const std::string& userId, int points, const std::string& reason);
    int getPoints(const std::string& userId);
    void redeemPoints(const std::string& userId, int points);
};

#endif

#include "LoyaltyPointsPlugin.h"

#include <stdexcept>
#include <unordered_map>

namespace { std::unordered_map<std::string, int> g_points; }

void LoyaltyPointsPlugin::initialize() { g_points.clear(); }
void LoyaltyPointsPlugin::awardPoints(const std::string& userId, int points, const std::string&) { if (points > 0) g_points[userId] += points; }
int LoyaltyPointsPlugin::getPoints(const std::string& userId) { return g_points[userId]; }
void LoyaltyPointsPlugin::redeemPoints(const std::string& userId, int points) {
    if (points <= 0 || g_points[userId] < points) throw std::runtime_error("Insufficient points");
    g_points[userId] -= points;
}

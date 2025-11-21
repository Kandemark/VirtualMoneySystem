/**
 * @file PointsTracker.cpp
 */

#include "PointsTracker.h"
#include <iostream>

PointsTracker::PointsTracker() {}

void PointsTracker::addPoints(const std::string& userId, int points) {
    userPoints[userId] += points;
    std::cout << "Added " << points << " points to " << userId << std::endl;
}

int PointsTracker::getPoints(const std::string& userId) const {
    auto it = userPoints.find(userId);
    if (it != userPoints.end()) {
        return it->second;
    }
    return 0;
}

bool PointsTracker::redeemPoints(const std::string& userId, int points) {
    auto it = userPoints.find(userId);
    if (it != userPoints.end() && it->second >= points) {
        it->second -= points;
        std::cout << "Redeemed " << points << " points for " << userId << std::endl;
        return true;
    }
    return false;
}

std::map<std::string, int> PointsTracker::getLeaderboard() const {
    return userPoints;
}

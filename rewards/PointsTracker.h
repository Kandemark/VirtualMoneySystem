/**
 * @file PointsTracker.h
 * @brief Rewards points tracking
 */

#ifndef POINTS_TRACKER_H
#define POINTS_TRACKER_H

#include <string>

class PointsTracker {
public:
    void addPoints(const std::string& userId, int points);
    int getPoints(const std::string& userId);
    void deductPoints(const std::string& userId, int points);
};

#endif

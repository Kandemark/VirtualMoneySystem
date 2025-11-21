#include "RewardsEngine.h"

double RewardsEngine::calculateReward(const std::string& userId, double transactionAmount) {
    return transactionAmount * 0.02;
}

void RewardsEngine::awardPoints(const std::string& userId, int points) {
    userPoints[userId] += points;
}

int RewardsEngine::getPoints(const std::string& userId) {
    auto it = userPoints.find(userId);
    return (it != userPoints.end()) ? it->second : 0;
}

bool RewardsEngine::redeemPoints(const std::string& userId, int points, double& cashValue) {
    if (getPoints(userId) >= points) {
        userPoints[userId] -= points;
        cashValue = points * pointsToCashRatio;
        return true;
    }
    return false;
}

#ifndef REWARDS_ENGINE_H
#define REWARDS_ENGINE_H
#include <string>
#include <map>

class RewardsEngine {
public:
    double calculateReward(const std::string& userId, double transactionAmount);
    void awardPoints(const std::string& userId, int points);
    int getPoints(const std::string& userId);
    bool redeemPoints(const std::string& userId, int points, double& cashValue);
private:
    std::map<std::string, int> userPoints;
    double pointsToCashRatio = 0.01;
};

#endif

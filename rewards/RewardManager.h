/**
 * @file RewardManager.h
 * @brief Reward management system
 */

#ifndef REWARD_MANAGER_H
#define REWARD_MANAGER_H

#include <string>

class RewardManager {
public:
    void createReward(const std::string& rewardId, const std::string& details);
    void assignReward(const std::string& userId, const std::string& rewardId);
    std::string getRewardStatus(const std::string& userId, const std::string& rewardId);
};

#endif

/**
 * @file RewardManager.cpp
 */

#include "RewardManager.h"
#include <iostream>

RewardManager::RewardManager() {}

void RewardManager::createReward(const std::string& rewardId, const std::string& name, int pointsCost) {
    Reward reward;
    reward.rewardId = rewardId;
    reward.name = name;
    reward.pointsCost = pointsCost;
    reward.available = true;
    
    rewards[rewardId] = reward;
    std::cout << "Reward created: " << name << " (" << pointsCost << " points)" << std::endl;
}

bool RewardManager::claimReward(const std::string& userId, const std::string& rewardId) {
    auto it = rewards.find(rewardId);
    if (it != rewards.end() && it->second.available) {
        std::cout << "Reward claimed: " << it->second.name << " by " << userId << std::endl;
        return true;
    }
    return false;
}

std::vector<Reward> RewardManager::getAvailableRewards() const {
    std::vector<Reward> available;
    for (const auto& [id, reward] : rewards) {
        if (reward.available) {
            available.push_back(reward);
        }
    }
    return available;
}

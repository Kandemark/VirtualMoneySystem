/**
 * @file TrialManager.cpp
 * @brief Implementation of the TrialManager class
 */

#include "TrialManager.h"

bool TrialManager::startTrial(const std::string& userId, const std::string& planId, int durationDays) {
    // Check if user already has an active trial
    if (isInTrial(userId)) {
        return false;
    }
    
    Trial trial;
    trial.userId = userId;
    trial.planId = planId;
    trial.startDate = std::chrono::system_clock::now();
    trial.endDate = trial.startDate + std::chrono::hours(24 * durationDays);
    trial.isActive = true;
    
    trials[userId] = trial;
    return true;
}

bool TrialManager::isInTrial(const std::string& userId) {
    auto it = trials.find(userId);
    if (it != trials.end()) {
        auto now = std::chrono::system_clock::now();
        return it->second.isActive && now < it->second.endDate;
    }
    return false;
}

bool TrialManager::convertToPaid(const std::string& userId) {
    auto it = trials.find(userId);
    if (it != trials.end()) {
        it->second.isActive = false;
        return true;
    }
    return false;
}

int TrialManager::getRemainingDays(const std::string& userId) {
    auto it = trials.find(userId);
    if (it != trials.end() && it->second.isActive) {
        auto now = std::chrono::system_clock::now();
        auto remaining = std::chrono::duration_cast<std::chrono::hours>(
            it->second.endDate - now).count();
        return static_cast<int>(remaining / 24);
    }
    return 0;
}

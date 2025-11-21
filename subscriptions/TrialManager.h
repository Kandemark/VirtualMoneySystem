/**
 * @file TrialManager.h
 * @brief Manages free trial periods for subscriptions
 * 
 * The TrialManager handles free trial creation, tracking, and conversion
 * to paid subscriptions.
 */

#ifndef TRIAL_MANAGER_H
#define TRIAL_MANAGER_H

#include <string>
#include <map>
#include <chrono>

/**
 * @brief Represents an active trial period
 */
struct Trial {
    std::string userId;           ///< User ID
    std::string planId;           ///< Plan being trialed
    std::chrono::system_clock::time_point startDate;  ///< Trial start date
    std::chrono::system_clock::time_point endDate;    ///< Trial end date
    bool isActive;                ///< Whether trial is currently active
};

/**
 * @brief Manages free trial periods
 */
class TrialManager {
public:
    /**
     * @brief Start a free trial for a user
     * @param userId The user identifier
     * @param planId The plan to trial
     * @param durationDays Trial duration in days
     * @return true if trial started successfully
     */
    bool startTrial(const std::string& userId, const std::string& planId, int durationDays = 14);
    
    /**
     * @brief Check if a user is currently in a trial
     * @param userId The user identifier
     * @return true if in active trial
     */
    bool isInTrial(const std::string& userId);
    
    /**
     * @brief Convert trial to paid subscription
     * @param userId The user identifier
     * @return true if conversion successful
     */
    bool convertToPaid(const std::string& userId);
    
    /**
     * @brief Get remaining trial days
     * @param userId The user identifier
     * @return Number of days remaining in trial
     */
    int getRemainingDays(const std::string& userId);

private:
    /// Map of user IDs to trial details
    std::map<std::string, Trial> trials;
};

#endif // TRIAL_MANAGER_H

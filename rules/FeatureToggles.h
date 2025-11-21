/**
 * @file FeatureToggles.h
 * @brief Feature flag management system
 */

#ifndef FEATURE_TOGGLES_H
#define FEATURE_TOGGLES_H

#include <string>
#include <map>

/**
 * @brief Manages feature flags for gradual rollouts
 */
class FeatureToggles {
public:
    /**
     * @brief Check if feature is enabled
     * @param featureName Feature identifier
     * @param userId Optional user ID for user-specific toggles
     * @return true if feature is enabled
     */
    bool isFeatureEnabled(const std::string& featureName, const std::string& userId = "");
    
    /**
     * @brief Enable feature
     * @param featureName Feature identifier
     * @param percentage Rollout percentage (0-100)
     */
    void enableFeature(const std::string& featureName, int percentage = 100);
    
    /**
     * @brief Disable feature
     * @param featureName Feature identifier
     */
    void disableFeature(const std::string& featureName);
    
    /**
     * @brief Get feature rollout percentage
     * @param featureName Feature identifier
     * @return Rollout percentage
     */
    int getFeaturePercentage(const std::string& featureName);

private:
    std::map<std::string, int> featureFlags;
};

#endif

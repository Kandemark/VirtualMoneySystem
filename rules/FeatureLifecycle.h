/**
 * @file FeatureLifecycle.h
 * @brief Manage feature lifecycle and deprecation
 */

#ifndef FEATURE_LIFECYCLE_H
#define FEATURE_LIFECYCLE_H

#include <string>
#include <map>

enum class FeatureStatus {
    BETA,
    STABLE,
    DEPRECATED,
    REMOVED
};

/**
 * @brief Manages feature lifecycle stages
 */
class FeatureLifecycle {
public:
    /**
     * @brief Set feature status
     * @param featureName Feature identifier
     * @param status Feature status
     */
    void setFeatureStatus(const std::string& featureName, FeatureStatus status);
    
    /**
     * @brief Get feature status
     * @param featureName Feature identifier
     * @return Current status
     */
    FeatureStatus getFeatureStatus(const std::string& featureName);
    
    /**
     * @brief Mark feature as deprecated
     * @param featureName Feature identifier
     * @param removalDate Planned removal date
     */
    void deprecateFeature(const std::string& featureName, const std::string& removalDate);

private:
    std::map<std::string, FeatureStatus> featureStatuses;
};

#endif

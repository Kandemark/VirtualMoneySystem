/**
 * @file FeatureToggles.h
 * @brief Feature toggles for settings directory
 */

#ifndef FEATURE_TOGGLES_SETTINGS_H
#define FEATURE_TOGGLES_SETTINGS_H

#include <string>

class FeatureTogglesSettings {
public:
    void enableFeature(const std::string& feature);
    void disableFeature(const std::string& feature);
    bool isFeatureEnabled(const std::string& feature);
};

#endif

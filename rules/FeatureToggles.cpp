/**
 * @file FeatureToggles.cpp
 */

#include "FeatureToggles.h"
#include <iostream>

FeatureToggles::FeatureToggles() {
    // Initialize default features
    features["cbdc_enabled"] = true;
    features["smart_contracts"] = true;
    features["quantum_crypto"] = true;
    features["gpu_acceleration"] = false;
    features["beta_features"] = false;
}

bool FeatureToggles::isEnabled(const std::string& featureName) const {
    auto it = features.find(featureName);
    if (it != features.end()) {
        return it->second;
    }
    return false;
}

void FeatureToggles::enable(const std::string& featureName) {
    features[featureName] = true;
    std::cout << "Feature enabled: " << featureName << std::endl;
}

void FeatureToggles::disable(const std::string& featureName) {
    features[featureName] = false;
    std::cout << "Feature disabled: " << featureName << std::endl;
}

std::map<std::string, bool> FeatureToggles::getAllFeatures() const {
    return features;
}

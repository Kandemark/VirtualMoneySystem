/**
 * @file FeatureLifecycle.cpp
 */

#include "FeatureLifecycle.h"
#include <iostream>

FeatureLifecycle::FeatureLifecycle() {}

void FeatureLifecycle::registerFeature(const std::string& featureName, const std::string& stage) {
    features[featureName] = stage;
    std::cout << "Feature registered: " << featureName << " (" << stage << ")" << std::endl;
}

std::string FeatureLifecycle::getStage(const std::string& featureName) const {
    auto it = features.find(featureName);
    if (it != features.end()) {
        return it->second;
    }
    return "unknown";
}

void FeatureLifecycle::promoteFeature(const std::string& featureName) {
    auto it = features.find(featureName);
    if (it != features.end()) {
        if (it->second == "alpha") it->second = "beta";
        else if (it->second == "beta") it->second = "stable";
        std::cout << "Feature promoted: " << featureName << " -> " << it->second << std::endl;
    }
}

void FeatureLifecycle::deprecateFeature(const std::string& featureName) {
    auto it = features.find(featureName);
    if (it != features.end()) {
        it->second = "deprecated";
        std::cout << "Feature deprecated: " << featureName << std::endl;
    }
}

/**
 * @file FeatureToggles.cpp (settings)
 */

#include "FeatureToggles.h"
#include <iostream>

namespace VirtualMoney {
namespace Settings {

FeatureToggles::FeatureToggles() {
    // Initialize default features
    features["new_ui"] = false;
    features["beta_api"] = false;
    features["experimental_features"] = false;
}

bool FeatureToggles::isEnabled(const std::string& feature) const {
    auto it = features.find(feature);
    if (it != features.end()) {
        return it->second;
    }
    return false;
}

void FeatureToggles::enable(const std::string& feature) {
    features[feature] = true;
    std::cout << "Feature enabled: " << feature << std::endl;
}

void FeatureToggles::disable(const std::string& feature) {
    features[feature] = false;
    std::cout << "Feature disabled: " << feature << std::endl;
}

} // namespace Settings
} // namespace VirtualMoney

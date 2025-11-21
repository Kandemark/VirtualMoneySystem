/**
 * @file SettingsManager.cpp
 */

#include "SettingsManager.h"
#include <iostream>

SettingsManager::SettingsManager() {
    // Default settings
    settings["api_timeout"] = "30";
    settings["max_connections"] = "1000";
    settings["log_level"] = "info";
}

std::string SettingsManager::get(const std::string& key) const {
    auto it = settings.find(key);
    if (it != settings.end()) {
        return it->second;
    }
    return "";
}

void SettingsManager::set(const std::string& key, const std::string& value) {
    settings[key] = value;
    std::cout << "Setting updated: " << key << " = " << value << std::endl;
}

std::map<std::string, std::string> SettingsManager::getAll() const {
    return settings;
}

bool SettingsManager::loadFromFile(const std::string& filename) {
    std::cout << "Loading settings from: " << filename << std::endl;
    return true;
}

bool SettingsManager::saveToFile(const std::string& filename) {
    std::cout << "Saving settings to: " << filename << std::endl;
    return true;
}

#include "ConfigManager.h"
#include <iostream>

void ConfigManager::loadConfig(const std::string& configFile) {
    std::cout << "[Config] Loading configuration from " << configFile << std::endl;
}

std::string ConfigManager::get(const std::string& key, const std::string& defaultValue) {
    auto it = config.find(key);
    return (it != config.end()) ? it->second : defaultValue;
}

void ConfigManager::set(const std::string& key, const std::string& value) {
    config[key] = value;
}

bool ConfigManager::getBool(const std::string& key, bool defaultValue) {
    auto value = get(key);
    if (value == "true" || value == "1") return true;
    if (value == "false" || value == "0") return false;
    return defaultValue;
}

int ConfigManager::getInt(const std::string& key, int defaultValue) {
    auto value = get(key);
    try {
        return std::stoi(value);
    } catch (...) {
        return defaultValue;
    }
}

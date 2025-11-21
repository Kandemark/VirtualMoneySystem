/**
 * @file ConfigManager.h
 * @brief Centralized configuration management
 */

#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

#include <string>
#include <map>

class ConfigManager {
public:
    void loadConfig(const std::string& configFile);
    std::string get(const std::string& key, const std::string& defaultValue = "");
    void set(const std::string& key, const std::string& value);
    bool getBool(const std::string& key, bool defaultValue = false);
    int getInt(const std::string& key, int defaultValue = 0);
private:
    std::map<std::string, std::string> config;
};

#endif

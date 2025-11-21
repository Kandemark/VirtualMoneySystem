/**
 * @file SettingsManager.h
 * @brief Application settings management
 */

#ifndef SETTINGS_MANAGER_H
#define SETTINGS_MANAGER_H

#include <string>
#include <map>

class SettingsManager {
public:
    std::string getSetting(const std::string& key);
    void setSetting(const std::string& key, const std::string& value);
    void loadSettings(const std::string& configFile);
    void saveSettings(const std::string& configFile);
    std::map<std::string, std::string> getAllSettings();
    void resetToDefaults();

private:
    std::map<std::string, std::string> settings;
};

#endif

/**
 * @file PluginAPI.h
 * @brief API for plugin development
 */

#ifndef PLUGIN_API_H
#define PLUGIN_API_H

#include <string>
#include <functional>

/**
 * @brief Plugin API for third-party developers
 */
class PluginAPI {
public:
    /**
     * @brief Register a hook callback
     * @param hookName Name of the hook point
     * @param callback Function to call when hook is triggered
     */
    void registerHook(const std::string& hookName, std::function<void(const std::string&)> callback);
    
    /**
     * @brief Trigger a hook
     * @param hookName Hook to trigger
     * @param data Data to pass to callbacks
     */
    void triggerHook(const std::string& hookName, const std::string& data);
    
    /**
     * @brief Get platform version
     * @return Platform version string
     */
    std::string getPlatformVersion();

private:
    std::map<std::string, std::vector<std::function<void(const std::string&)>>> hooks;
};

#endif

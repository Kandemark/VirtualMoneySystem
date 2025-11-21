/**
 * @file PluginManager.h
 * @brief Plugin system for extensibility
 * 
 * Manages third-party plugins and extensions to extend platform functionality
 */

#ifndef PLUGIN_MANAGER_H
#define PLUGIN_MANAGER_H

#include <string>
#include <map>
#include <vector>

/**
 * @brief Represents a plugin
 */
struct Plugin {
    std::string pluginId;        ///< Unique plugin identifier
    std::string name;            ///< Plugin display name
    std::string version;         ///< Plugin version
    bool isEnabled;              ///< Whether plugin is active
    std::string author;          ///< Plugin author
};

/**
 * @brief Manages platform plugins
 */
class PluginManager {
public:
    /**
     * @brief Register a new plugin
     * @param plugin Plugin details
     * @return true if registration successful
     */
    bool registerPlugin(const Plugin& plugin);
    
    /**
     * @brief Enable a plugin
     * @param pluginId Plugin identifier
     * @return true if enabled successfully
     */
    bool enablePlugin(const std::string& pluginId);
    
    /**
     * @brief Disable a plugin
     * @param pluginId Plugin identifier
     * @return true if disabled successfully
     */
    bool disablePlugin(const std::string& pluginId);
    
    /**
     * @brief Get all registered plugins
     * @return Vector of all plugins
     */
    std::vector<Plugin> getAllPlugins();
    
    /**
     * @brief Check if plugin is enabled
     * @param pluginId Plugin identifier
     * @return true if plugin is enabled
     */
    bool isPluginEnabled(const std::string& pluginId);

private:
    std::map<std::string, Plugin> plugins;  ///< Map of plugin IDs to plugins
};

#endif // PLUGIN_MANAGER_H

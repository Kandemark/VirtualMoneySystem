/**
 * @file PluginManager.cpp
 * @brief Implementation of PluginManager
 */

#include "PluginManager.h"

bool PluginManager::registerPlugin(const Plugin& plugin) {
    plugins[plugin.pluginId] = plugin;
    return true;
}

bool PluginManager::enablePlugin(const std::string& pluginId) {
    auto it = plugins.find(pluginId);
    if (it != plugins.end()) {
        it->second.isEnabled = true;
        return true;
    }
    return false;
}

bool PluginManager::disablePlugin(const std::string& pluginId) {
    auto it = plugins.find(pluginId);
    if (it != plugins.end()) {
        it->second.isEnabled = false;
        return true;
    }
    return false;
}

std::vector<Plugin> PluginManager::getAllPlugins() {
    std::vector<Plugin> result;
    for (const auto& [id, plugin] : plugins) {
        result.push_back(plugin);
    }
    return result;
}

bool PluginManager::isPluginEnabled(const std::string& pluginId) {
    auto it = plugins.find(pluginId);
    return (it != plugins.end() && it->second.isEnabled);
}

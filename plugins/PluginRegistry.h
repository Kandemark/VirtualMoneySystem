/**
 * @file PluginRegistry.h
 * @brief Plugin registry
 */

#ifndef PLUGIN_REGISTRY_H
#define PLUGIN_REGISTRY_H

#include <string>
#include <vector>

class PluginRegistry {
public:
    void registerPlugin(const std::string& pluginId, const std::string& metadata);
    void unregisterPlugin(const std::string& pluginId);
    std::vector<std::string> listPlugins();
    std::string getPluginInfo(const std::string& pluginId);
};

#endif

/**
 * @file PluginLoader.h
 * @brief Plugin loading system
 */

#ifndef PLUGIN_LOADER_H
#define PLUGIN_LOADER_H

#include <string>

class PluginLoader {
public:
    bool loadPlugin(const std::string& pluginPath);
    void unloadPlugin(const std::string& pluginId);
    bool isPluginLoaded(const std::string& pluginId);
    void reloadPlugin(const std::string& pluginId);
};

#endif

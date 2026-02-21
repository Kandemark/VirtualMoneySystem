#include "PluginLoader.h"

#include <unordered_set>

namespace { std::unordered_set<std::string> g_loaded; }

bool PluginLoader::loadPlugin(const std::string& pluginPath) {
    if (pluginPath.empty()) return false;
    g_loaded.insert(pluginPath);
    return true;
}

void PluginLoader::unloadPlugin(const std::string& pluginId) { g_loaded.erase(pluginId); }
bool PluginLoader::isPluginLoaded(const std::string& pluginId) { return g_loaded.count(pluginId) > 0; }
void PluginLoader::reloadPlugin(const std::string& pluginId) { if (isPluginLoaded(pluginId)) { unloadPlugin(pluginId); loadPlugin(pluginId); } }

/**
 * @file PluginRegistry.cpp
 */

#include "PluginRegistry.h"
#include <iostream>

namespace VirtualMoney {

PluginRegistry::PluginRegistry() {}

bool PluginRegistry::registerPlugin(const std::string& pluginName, const std::string& version) {
    Plugin plugin;
    plugin.name = pluginName;
    plugin.version = version;
    plugin.enabled = true;
    
    plugins[pluginName] = plugin;
    
    std::cout << "Plugin registered: " << pluginName << " v" << version << std::endl;
    
    return true;
}

bool PluginRegistry::enablePlugin(const std::string& pluginName) {
    auto it = plugins.find(pluginName);
    if (it != plugins.end()) {
        it->second.enabled = true;
        std::cout << "Plugin enabled: " << pluginName << std::endl;
        return true;
    }
    return false;
}

bool PluginRegistry::disablePlugin(const std::string& pluginName) {
    auto it = plugins.find(pluginName);
    if (it != plugins.end()) {
        it->second.enabled = false;
        std::cout << "Plugin disabled: " << pluginName << std::endl;
        return true;
    }
    return false;
}

std::vector<Plugin> PluginRegistry::getEnabledPlugins() const {
    std::vector<Plugin> enabled;
    for (const auto& [name, plugin] : plugins) {
        if (plugin.enabled) {
            enabled.push_back(plugin);
        }
    }
    return enabled;
}

} // namespace VirtualMoney

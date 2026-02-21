#include "DeveloperMarketplace.h"

#include <unordered_map>

namespace { std::unordered_map<std::string, std::string> g_plugins; }

void DeveloperMarketplace::listPlugin(const std::string& pluginId, const std::string& metadata) { g_plugins[pluginId] = metadata; }

std::vector<std::string> DeveloperMarketplace::searchPlugins(const std::string& query) {
    std::vector<std::string> out;
    for (const auto& [id, meta] : g_plugins) if (id.find(query) != std::string::npos || meta.find(query) != std::string::npos) out.push_back(id);
    return out;
}

void DeveloperMarketplace::installPlugin(const std::string& pluginId) { g_plugins[pluginId] += "|installed"; }
void DeveloperMarketplace::uninstallPlugin(const std::string& pluginId) { g_plugins.erase(pluginId); }

/**
 * @file DeveloperMarketplace.h
 * @brief Developer plugin marketplace
 */

#ifndef DEVELOPER_MARKETPLACE_H
#define DEVELOPER_MARKETPLACE_H

#include <string>
#include <vector>

class DeveloperMarketplace {
public:
    void listPlugin(const std::string& pluginId, const std::string& metadata);
    std::vector<std::string> searchPlugins(const std::string& query);
    void installPlugin(const std::string& pluginId);
    void uninstallPlugin(const std::string& pluginId);
};

#endif

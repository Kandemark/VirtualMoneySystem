#include "TenantConfig.h"

void TenantConfig::setConfig(const std::string& tenantId, const std::string& key, const std::string& value) {
    configs[tenantId][key] = value;
}

std::string TenantConfig::getConfig(const std::string& tenantId, const std::string& key) {
    auto tenantIt = configs.find(tenantId);
    if (tenantIt != configs.end()) {
        auto keyIt = tenantIt->second.find(key);
        if (keyIt != tenantIt->second.end()) {
            return keyIt->second;
        }
    }
    return "";
}

std::map<std::string, std::string> TenantConfig::getAllConfig(const std::string& tenantId) {
    return configs[tenantId];
}

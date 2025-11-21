/**
 * @file TenantConfig.h
 * @brief Per-tenant configuration management
 */

#ifndef TENANT_CONFIG_H
#define TENANT_CONFIG_H

#include <string>
#include <map>

class TenantConfig {
public:
    void setConfig(const std::string& tenantId, const std::string& key, const std::string& value);
    std::string getConfig(const std::string& tenantId, const std::string& key);
    std::map<std::string, std::string> getAllConfig(const std::string& tenantId);
private:
    std::map<std::string, std::map<std::string, std::string>> configs;
};

#endif

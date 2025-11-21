/**
 * @file TenantManager.h
 * @brief Multi-tenant organization management
 */

#ifndef TENANT_MANAGER_H
#define TENANT_MANAGER_H

#include <string>
#include <map>
#include <vector>

struct Tenant {
    std::string tenantId;
    std::string name;
    std::string domain;
    bool isActive;
    int maxUsers;
};

class TenantManager {
public:
    std::string createTenant(const std::string& name, const std::string& domain);
    Tenant getTenant(const std::string& tenantId);
    void deactivateTenant(const std::string& tenantId);
    std::vector<std::string> getTenantUsers(const std::string& tenantId);
private:
    std::map<std::string, Tenant> tenants;
    std::map<std::string, std::vector<std::string>> tenantUsers;
};

#endif

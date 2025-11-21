#include "TenantManager.h"
#include <random>

std::string TenantManager::createTenant(const std::string& name, const std::string& domain) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(100000, 999999);
    
    std::string tenantId = "TENANT_" + std::to_string(dis(gen));
    Tenant tenant;
    tenant.tenantId = tenantId;
    tenant.name = name;
    tenant.domain = domain;
    tenant.isActive = true;
    tenant.maxUsers = 100;
    
    tenants[tenantId] = tenant;
    return tenantId;
}

Tenant TenantManager::getTenant(const std::string& tenantId) {
    return tenants.at(tenantId);
}

void TenantManager::deactivateTenant(const std::string& tenantId) {
    auto it = tenants.find(tenantId);
    if (it != tenants.end()) {
        it->second.isActive = false;
    }
}

std::vector<std::string> TenantManager::getTenantUsers(const std::string& tenantId) {
    return tenantUsers[tenantId];
}

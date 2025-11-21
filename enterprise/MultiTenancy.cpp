/**
 * @file MultiTenancy.cpp
 */

#include "MultiTenancy.h"
#include <iostream>
#include <random>
#include <sstream>

namespace VirtualMoney {

MultiTenancy::MultiTenancy() {}

std::string MultiTenancy::createTenant(const std::string& name, const std::string& domain) {
    std::string tenantId = generateTenantId();
    
    Tenant tenant;
    tenant.tenantId = tenantId;
    tenant.name = name;
    tenant.domain = domain;
    tenant.active = true;
    
    // Default quotas
    tenant.quotas["users"] = 1000;
    tenant.quotas["transactions"] = 100000;
    tenant.quotas["api_calls"] = 1000000;
    tenant.quotas["storage_gb"] = 100;
    
    // Default features
    tenant.features["api_access"] = true;
    tenant.features["white_label"] = false;
    tenant.features["custom_domain"] = false;
    tenant.features["advanced_analytics"] = false;
    
    tenants[tenantId] = tenant;
    
    // Initialize usage
    TenantUsage usage;
    usage.users = 0;
    usage.transactions = 0;
    usage.apiCalls = 0;
    usage.storageGB = 0.0;
    this->usage[tenantId] = usage;
    
    std::cout << "Tenant created: " << name << " (" << tenantId << ")" << std::endl;
    std::cout << "Domain: " << domain << std::endl;
    
    return tenantId;
}

Tenant MultiTenancy::getTenant(const std::string& tenantId) {
    auto it = tenants.find(tenantId);
    if (it != tenants.end()) {
        return it->second;
    }
    return Tenant();
}

Tenant MultiTenancy::getTenantByDomain(const std::string& domain) {
    for (const auto& [id, tenant] : tenants) {
        if (tenant.domain == domain) {
            return tenant;
        }
    }
    return Tenant();
}

bool MultiTenancy::updateBranding(const std::string& tenantId, const std::map<std::string, std::string>& branding) {
    auto it = tenants.find(tenantId);
    if (it != tenants.end()) {
        it->second.branding = branding;
        std::cout << "Branding updated for tenant: " << tenantId << std::endl;
        return true;
    }
    return false;
}

bool MultiTenancy::setFeature(const std::string& tenantId, const std::string& feature, bool enabled) {
    auto it = tenants.find(tenantId);
    if (it != tenants.end()) {
        it->second.features[feature] = enabled;
        std::cout << "Feature " << feature << " " << (enabled ? "enabled" : "disabled") 
                  << " for tenant: " << tenantId << std::endl;
        return true;
    }
    return false;
}

bool MultiTenancy::setQuota(const std::string& tenantId, const std::string& resource, int limit) {
    auto it = tenants.find(tenantId);
    if (it != tenants.end()) {
        it->second.quotas[resource] = limit;
        std::cout << "Quota set for tenant " << tenantId << ": " << resource << " = " << limit << std::endl;
        return true;
    }
    return false;
}

bool MultiTenancy::hasFeature(const std::string& tenantId, const std::string& feature) {
    auto it = tenants.find(tenantId);
    if (it != tenants.end()) {
        auto featureIt = it->second.features.find(feature);
        if (featureIt != it->second.features.end()) {
            return featureIt->second;
        }
    }
    return false;
}

bool MultiTenancy::checkQuota(const std::string& tenantId, const std::string& resource) {
    auto tenantIt = tenants.find(tenantId);
    auto usageIt = usage.find(tenantId);
    
    if (tenantIt == tenants.end() || usageIt == usage.end()) {
        return false;
    }
    
    auto quotaIt = tenantIt->second.quotas.find(resource);
    if (quotaIt == tenantIt->second.quotas.end()) {
        return true; // No quota set
    }
    
    if (resource == "users") {
        return usageIt->second.users < quotaIt->second;
    } else if (resource == "transactions") {
        return usageIt->second.transactions < quotaIt->second;
    } else if (resource == "api_calls") {
        return usageIt->second.apiCalls < quotaIt->second;
    }
    
    return true;
}

TenantUsage MultiTenancy::getUsage(const std::string& tenantId) {
    auto it = usage.find(tenantId);
    if (it != usage.end()) {
        return it->second;
    }
    return TenantUsage();
}

std::string MultiTenancy::getTenantSchema(const std::string& tenantId) {
    return "tenant_" + tenantId;
}

bool MultiTenancy::setActive(const std::string& tenantId, bool active) {
    auto it = tenants.find(tenantId);
    if (it != tenants.end()) {
        it->second.active = active;
        std::cout << "Tenant " << tenantId << " " << (active ? "activated" : "deactivated") << std::endl;
        return true;
    }
    return false;
}

std::string MultiTenancy::generateTenantId() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(100000, 999999);
    
    std::stringstream ss;
    ss << "TENANT_" << dis(gen);
    return ss.str();
}

} // namespace VirtualMoney

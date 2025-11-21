/**
 * @file MultiTenancy.h
 * @brief Multi-tenancy support for enterprise
 */

#ifndef MULTI_TENANCY_H
#define MULTI_TENANCY_H

#include <string>
#include <map>
#include <vector>

namespace VirtualMoney {

struct Tenant {
    std::string tenantId;
    std::string name;
    std::string domain;
    std::map<std::string, std::string> branding;
    std::map<std::string, bool> features;
    std::map<std::string, int> quotas;
    bool active;
};

struct TenantUsage {
    int users;
    int transactions;
    int apiCalls;
    double storageGB;
};

class MultiTenancy {
public:
    MultiTenancy();
    
    /**
     * @brief Create new tenant
     */
    std::string createTenant(const std::string& name, const std::string& domain);
    
    /**
     * @brief Get tenant by ID
     */
    Tenant getTenant(const std::string& tenantId);
    
    /**
     * @brief Get tenant by domain
     */
    Tenant getTenantByDomain(const std::string& domain);
    
    /**
     * @brief Update tenant branding
     */
    bool updateBranding(const std::string& tenantId, const std::map<std::string, std::string>& branding);
    
    /**
     * @brief Set tenant feature
     */
    bool setFeature(const std::string& tenantId, const std::string& feature, bool enabled);
    
    /**
     * @brief Set tenant quota
     */
    bool setQuota(const std::string& tenantId, const std::string& resource, int limit);
    
    /**
     * @brief Check if tenant has feature
     */
    bool hasFeature(const std::string& tenantId, const std::string& feature);
    
    /**
     * @brief Check quota
     */
    bool checkQuota(const std::string& tenantId, const std::string& resource);
    
    /**
     * @brief Get tenant usage
     */
    TenantUsage getUsage(const std::string& tenantId);
    
    /**
     * @brief Isolate tenant data
     */
    std::string getTenantSchema(const std::string& tenantId);
    
    /**
     * @brief Activate/deactivate tenant
     */
    bool setActive(const std::string& tenantId, bool active);
    
private:
    std::map<std::string, Tenant> tenants;
    std::map<std::string, TenantUsage> usage;
    
    std::string generateTenantId();
};

} // namespace VirtualMoney

#endif

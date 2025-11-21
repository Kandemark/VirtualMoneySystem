/**
 * @file ResourceIsolation.h
 * @brief Resource isolation for multi-tenancy
 */

#ifndef RESOURCE_ISOLATION_H
#define RESOURCE_ISOLATION_H

#include <string>

class ResourceIsolation {
public:
    void allocateResources(const std::string& tenantId, int cpuLimit, int memoryLimit);
    void enforceQuotas(const std::string& tenantId);
    std::string getResourceUsage(const std::string& tenantId);
};

#endif

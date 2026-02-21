#include "ResourceIsolation.h"

#include <unordered_map>

namespace { std::unordered_map<std::string, std::pair<int,int>> g_limits; }

void ResourceIsolation::allocateResources(const std::string& tenantId, int cpuLimit, int memoryLimit) { g_limits[tenantId] = {cpuLimit, memoryLimit}; }
void ResourceIsolation::enforceQuotas(const std::string& tenantId) { if (!g_limits.count(tenantId)) g_limits[tenantId] = {1, 256}; }
std::string ResourceIsolation::getResourceUsage(const std::string& tenantId) {
    auto it = g_limits.find(tenantId);
    if (it == g_limits.end()) return "cpu=0,memory=0";
    return "cpu=" + std::to_string(it->second.first) + ",memory=" + std::to_string(it->second.second);
}

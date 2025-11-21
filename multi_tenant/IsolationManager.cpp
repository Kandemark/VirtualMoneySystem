#include "IsolationManager.h"

bool IsolationManager::validateAccess(const std::string& tenantId, const std::string& resourceId) {
    auto it = resourceOwners.find(resourceId);
    if (it != resourceOwners.end()) {
        return it->second == tenantId;
    }
    return false;
}

void IsolationManager::setResourceOwner(const std::string& resourceId, const std::string& tenantId) {
    resourceOwners[resourceId] = tenantId;
}

std::string IsolationManager::getResourceOwner(const std::string& resourceId) {
    auto it = resourceOwners.find(resourceId);
    return (it != resourceOwners.end()) ? it->second : "";
}

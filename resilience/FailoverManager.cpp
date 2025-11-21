#include "FailoverManager.h"

void FailoverManager::registerPrimary(const std::string& serviceId, const std::string& endpoint) {
    primaryEndpoints[serviceId] = endpoint;
    isFailedOver[serviceId] = false;
}

void FailoverManager::registerBackup(const std::string& serviceId, const std::string& endpoint) {
    backupEndpoints[serviceId].push_back(endpoint);
}

std::string FailoverManager::getActiveEndpoint(const std::string& serviceId) {
    if (isFailedOver[serviceId] && !backupEndpoints[serviceId].empty()) {
        return backupEndpoints[serviceId][0];
    }
    return primaryEndpoints[serviceId];
}

bool FailoverManager::triggerFailover(const std::string& serviceId) {
    if (!backupEndpoints[serviceId].empty()) {
        isFailedOver[serviceId] = true;
        return true;
    }
    return false;
}

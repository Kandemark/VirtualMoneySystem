#include "AccessControl.h"

bool AccessControl::grantAccess(const std::string& userId, const std::string& resource) {
    userResources[userId].insert(resource);
    return true;
}

bool AccessControl::revokeAccess(const std::string& userId, const std::string& resource) {
    auto it = userResources.find(userId);
    if (it != userResources.end()) {
        return it->second.erase(resource) > 0;
    }
    return false;
}

bool AccessControl::hasAccess(const std::string& userId, const std::string& resource) const {
    auto it = userResources.find(userId);
    if (it != userResources.end()) {
        return it->second.count(resource) > 0;
    }
    return false;
}

std::set<std::string> AccessControl::getUserResources(const std::string& userId) const {
    auto it = userResources.find(userId);
    return (it != userResources.end()) ? it->second : std::set<std::string>{};
}

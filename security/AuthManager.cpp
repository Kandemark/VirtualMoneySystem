#include "AuthManager.h"
#include <set>

bool AuthManager::authenticate(const std::string& userId, const std::string& password) {
    auto it = credentials.find(userId);
    return (it != credentials.end() && it->second == password);
}

bool AuthManager::authorize(const std::string& userId, const std::string& action) {
    auto it = permissions.find(userId);
    if (it != permissions.end()) {
        return it->second.count(action) > 0;
    }
    return false;
}

void AuthManager::grantPermission(const std::string& userId, const std::string& action) {
    permissions[userId].insert(action);
}

void AuthManager::revokePermission(const std::string& userId, const std::string& action) {
    auto it = permissions.find(userId);
    if (it != permissions.end()) {
        it->second.erase(action);
    }
}

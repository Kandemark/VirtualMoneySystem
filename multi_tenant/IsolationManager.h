/**
 * @file IsolationManager.h
 * @brief Data isolation between tenants
 */

#ifndef ISOLATION_MANAGER_H
#define ISOLATION_MANAGER_H

#include <string>
#include <map>

class IsolationManager {
public:
    bool validateAccess(const std::string& tenantId, const std::string& resourceId);
    void setResourceOwner(const std::string& resourceId, const std::string& tenantId);
    std::string getResourceOwner(const std::string& resourceId);
private:
    std::map<std::string, std::string> resourceOwners;
};

#endif

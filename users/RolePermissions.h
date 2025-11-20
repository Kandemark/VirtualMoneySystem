#ifndef ROLE_PERMISSIONS_H
#define ROLE_PERMISSIONS_H

#include <string>
#include <set>
#include <map>

enum class Permission {
    VIEW_TRANSACTIONS,
    CREATE_TRANSACTION,
    MANAGE_USERS,
    VIEW_ANALYTICS,
    MANAGE_SETTINGS,
    APPROVE_KYC,
    SUSPEND_ACCOUNTS,
    ADMIN_ACCESS
};

class RolePermissions {
public:
    RolePermissions();
    void assignRole(const std::string& userId, const std::string& role);
    void addPermission(const std::string& role, Permission permission);
    bool hasPermission(const std::string& userId, Permission permission) const;
    std::set<Permission> getUserPermissions(const std::string& userId) const;

private:
    std::map<std::string, std::string> userRoles;
    std::map<std::string, std::set<Permission>> rolePermissions;
    void initializeDefaultRoles();
};

#endif

#include "RolePermissions.h"

RolePermissions::RolePermissions() { initializeDefaultRoles(); }

void RolePermissions::assignRole(const std::string& userId, const std::string& role) {
    userRoles[userId] = role;
}

void RolePermissions::addPermission(const std::string& role, Permission permission) {
    rolePermissions[role].insert(permission);
}

bool RolePermissions::hasPermission(const std::string& userId, Permission permission) const {
    auto it = userRoles.find(userId);
    if (it == userRoles.end()) return false;
    auto perms = rolePermissions.find(it->second);
    if (perms == rolePermissions.end()) return false;
    return perms->second.count(permission) > 0;
}

std::set<Permission> RolePermissions::getUserPermissions(const std::string& userId) const {
    auto it = userRoles.find(userId);
    if (it == userRoles.end()) return {};
    auto perms = rolePermissions.find(it->second);
    return (perms != rolePermissions.end()) ? perms->second : std::set<Permission>{};
}

void RolePermissions::initializeDefaultRoles() {
    addPermission("admin", Permission::ADMIN_ACCESS);
    addPermission("admin", Permission::MANAGE_USERS);
    addPermission("admin", Permission::APPROVE_KYC);
    addPermission("user", Permission::VIEW_TRANSACTIONS);
    addPermission("user", Permission::CREATE_TRANSACTION);
}

/**
 * @file AdminAuditTrail.h
 * @brief Admin action audit trail
 */

#ifndef ADMIN_AUDIT_TRAIL_H
#define ADMIN_AUDIT_TRAIL_H

#include <string>
#include <vector>

class AdminAuditTrail {
public:
    void recordAdminAction(const std::string& adminId, const std::string& action, const std::string& target);
    std::vector<std::string> getAuditTrail(const std::string& adminId);
    void exportAuditTrail(const std::string& filename);
};

#endif

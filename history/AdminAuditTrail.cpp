#include "AdminAuditTrail.h"

#include <fstream>
#include <unordered_map>

namespace { std::unordered_map<std::string, std::vector<std::string>> g_audit; }

void AdminAuditTrail::recordAdminAction(const std::string& adminId, const std::string& action, const std::string& target) {
    g_audit[adminId].push_back(action + ":" + target);
}

std::vector<std::string> AdminAuditTrail::getAuditTrail(const std::string& adminId) { return g_audit[adminId]; }

void AdminAuditTrail::exportAuditTrail(const std::string& filename) {
    std::ofstream out(filename);
    for (const auto& [admin, entries] : g_audit) for (const auto& e : entries) out << admin << ',' << e << '
';
}

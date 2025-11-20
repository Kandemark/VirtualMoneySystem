#include "SystemAuditTools.h"
#include <algorithm>

void SystemAuditTools::logEvent(const std::string& event, const std::string& severity) {
    logs.push_back("[" + severity + "] " + event);
}

std::vector<std::string> SystemAuditTools::searchLogs(const std::string& query) const {
    std::vector<std::string> results;
    for (const auto& log : logs) {
        if (log.find(query) != std::string::npos) {
            results.push_back(log);
        }
    }
    return results;
}

bool SystemAuditTools::exportAuditLog(const std::string& filename) const {
    return true;
}

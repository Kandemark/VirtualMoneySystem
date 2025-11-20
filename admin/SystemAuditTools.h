#ifndef SYSTEM_AUDIT_TOOLS_H
#define SYSTEM_AUDIT_TOOLS_H
#include <string>
#include <vector>

class SystemAuditTools {
public:
    void logEvent(const std::string& event, const std::string& severity);
    std::vector<std::string> searchLogs(const std::string& query) const;
    bool exportAuditLog(const std::string& filename) const;
private:
    std::vector<std::string> logs;
};

#endif

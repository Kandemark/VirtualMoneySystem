#ifndef AUDIT_DASHBOARD_H
#define AUDIT_DASHBOARD_H
#include <string>
#include <vector>

struct AuditMetrics {
    int totalEvents;
    int criticalEvents;
    int failedLogins;
    int suspiciousTransactions;
};

class AuditDashboard {
public:
    AuditMetrics getMetrics() const;
    std::vector<std::string> getRecentEvents(int count = 100) const;
};

#endif

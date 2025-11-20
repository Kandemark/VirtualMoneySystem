#include "AuditDashboard.h"

AuditMetrics AuditDashboard::getMetrics() const {
    AuditMetrics metrics;
    metrics.totalEvents = 10000;
    metrics.criticalEvents = 5;
    metrics.failedLogins = 100;
    metrics.suspiciousTransactions = 10;
    return metrics;
}

std::vector<std::string> AuditDashboard::getRecentEvents(int count) const {
    return {"Event 1", "Event 2", "Event 3"};
}

/**
 * @file RealtimeMonitor.h
 * @brief Real-time system monitoring and metrics
 */

#ifndef REALTIME_MONITOR_H
#define REALTIME_MONITOR_H

#include <string>
#include <map>
#include <vector>
#include <chrono>

namespace VirtualMoney {

struct SystemMetrics {
    double tps;                    // Transactions per second
    double avgLatencyMs;           // Average latency
    double cpuUsage;               // CPU usage percentage
    double memoryUsageMB;          // Memory usage in MB
    int activeConnections;         // Active connections
    double errorRate;              // Error rate percentage
    std::chrono::system_clock::time_point timestamp;
};

class RealtimeMonitor {
public:
    RealtimeMonitor();
    
    void recordTransaction(double latencyMs);
    void recordError(const std::string& errorType);
    void updateSystemMetrics();
    SystemMetrics getCurrentMetrics() const;
    std::vector<SystemMetrics> getMetricsHistory(int seconds) const;
    
    struct Alert {
        std::string severity;      // "critical", "warning", "info"
        std::string message;
        std::chrono::system_clock::time_point timestamp;
    };
    std::vector<Alert> getActiveAlerts() const;
    
    bool isHealthy() const;
    
private:
    SystemMetrics currentMetrics;
    std::vector<SystemMetrics> metricsHistory;
    std::vector<Alert> alerts;
    
    void checkThresholds();
    void generateAlert(const std::string& severity, const std::string& message);
};

} // namespace VirtualMoney

#endif

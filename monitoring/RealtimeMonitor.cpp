/**
 * @file RealtimeMonitor.cpp
 */

#include "RealtimeMonitor.h"
#include <algorithm>
#include <iostream>

namespace VirtualMoney {

RealtimeMonitor::RealtimeMonitor() {
    currentMetrics.tps = 0.0;
    currentMetrics.avgLatencyMs = 0.0;
    currentMetrics.cpuUsage = 0.0;
    currentMetrics.memoryUsageMB = 0.0;
    currentMetrics.activeConnections = 0;
    currentMetrics.errorRate = 0.0;
    currentMetrics.timestamp = std::chrono::system_clock::now();
}

void RealtimeMonitor::recordTransaction(double latencyMs) {
    currentMetrics.tps += 1.0;
    currentMetrics.avgLatencyMs = 
        (currentMetrics.avgLatencyMs + latencyMs) / 2.0;
    
    checkThresholds();
}

void RealtimeMonitor::recordError(const std::string& errorType) {
    currentMetrics.errorRate += 0.01;
    
    if (currentMetrics.errorRate > 5.0) {
        generateAlert("critical", "High error rate: " + std::to_string(currentMetrics.errorRate) + "%");
    }
}

void RealtimeMonitor::updateSystemMetrics() {
    // Update system metrics (CPU, memory, etc.)
    currentMetrics.cpuUsage = 45.5;      // Example
    currentMetrics.memoryUsageMB = 2048.0; // Example
    currentMetrics.activeConnections = 150;
    currentMetrics.timestamp = std::chrono::system_clock::now();
    
    metricsHistory.push_back(currentMetrics);
    
    // Keep only last 3600 seconds (1 hour)
    if (metricsHistory.size() > 3600) {
        metricsHistory.erase(metricsHistory.begin());
    }
    
    checkThresholds();
}

SystemMetrics RealtimeMonitor::getCurrentMetrics() const {
    return currentMetrics;
}

std::vector<SystemMetrics> RealtimeMonitor::getMetricsHistory(int seconds) const {
    std::vector<SystemMetrics> recent;
    
    if (metricsHistory.size() <= static_cast<size_t>(seconds)) {
        return metricsHistory;
    }
    
    auto start = metricsHistory.end() - seconds;
    recent.insert(recent.end(), start, metricsHistory.end());
    
    return recent;
}

std::vector<RealtimeMonitor::Alert> RealtimeMonitor::getActiveAlerts() const {
    return alerts;
}

bool RealtimeMonitor::isHealthy() const {
    if (currentMetrics.errorRate > 5.0) return false;
    if (currentMetrics.avgLatencyMs > 1000.0) return false;
    if (currentMetrics.cpuUsage > 90.0) return false;
    return true;
}

void RealtimeMonitor::checkThresholds() {
    // Check latency
    if (currentMetrics.avgLatencyMs > 500.0) {
        generateAlert("warning", "High latency: " + std::to_string(currentMetrics.avgLatencyMs) + "ms");
    }
    
    // Check CPU
    if (currentMetrics.cpuUsage > 80.0) {
        generateAlert("warning", "High CPU usage: " + std::to_string(currentMetrics.cpuUsage) + "%");
    }
}

void RealtimeMonitor::generateAlert(const std::string& severity, const std::string& message) {
    Alert alert;
    alert.severity = severity;
    alert.message = message;
    alert.timestamp = std::chrono::system_clock::now();
    
    alerts.push_back(alert);
    
    std::cout << "[" << severity << "] " << message << std::endl;
    
    // Keep only last 100 alerts
    if (alerts.size() > 100) {
        alerts.erase(alerts.begin());
    }
}

} // namespace VirtualMoney

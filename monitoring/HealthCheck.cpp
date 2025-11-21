/**
 * @file HealthCheck.cpp
 */

#include "HealthCheck.h"
#include <iostream>
#include <sstream>
#include <chrono>

namespace VirtualMoney {

HealthCheck::HealthCheck() {
    startTime = std::chrono::duration_cast<std::chrono::seconds>(
        std::chrono::system_clock::now().time_since_epoch()
    ).count();
}

HealthStatus HealthCheck::getHealth() {
    HealthStatus status;
    status.version = "2.0.0";
    status.uptime = calculateUptime();
    status.timestamp = std::time(nullptr);
    
    // Check all services
    status.services["database"] = checkDatabase() ? "up" : "down";
    status.services["cache"] = checkCache() ? "up" : "down";
    status.services["queue"] = checkQueue() ? "up" : "down";
    status.services["api"] = checkAPI() ? "up" : "down";
    
    // Determine overall status
    bool allHealthy = true;
    for (const auto& [service, state] : status.services) {
        if (state == "down") {
            allHealthy = false;
            break;
        }
    }
    
    status.status = allHealthy ? "healthy" : "degraded";
    
    return status;
}

bool HealthCheck::checkService(const std::string& serviceName) {
    if (serviceName == "database") return checkDatabase();
    if (serviceName == "cache") return checkCache();
    if (serviceName == "queue") return checkQueue();
    if (serviceName == "api") return checkAPI();
    return false;
}

std::string HealthCheck::getDetailedReport() {
    auto health = getHealth();
    
    std::stringstream report;
    report << "=== VirtualMoney System Health Report ===\n";
    report << "Status: " << health.status << "\n";
    report << "Version: " << health.version << "\n";
    report << "Uptime: " << health.uptime << "%\n";
    report << "\nServices:\n";
    
    for (const auto& [service, state] : health.services) {
        report << "  " << service << ": " << state << "\n";
    }
    
    return report.str();
}

bool HealthCheck::checkDatabase() {
    // In production: ping database
    return true;
}

bool HealthCheck::checkCache() {
    // In production: check Redis connection
    return true;
}

bool HealthCheck::checkQueue() {
    // In production: check message queue
    return true;
}

bool HealthCheck::checkAPI() {
    // In production: check API responsiveness
    return true;
}

double HealthCheck::calculateUptime() {
    long long now = std::chrono::duration_cast<std::chrono::seconds>(
        std::chrono::system_clock::now().time_since_epoch()
    ).count();
    
    long long uptimeSeconds = now - startTime;
    return 99.99; // Simplified - in production, calculate from actual downtime
}

} // namespace VirtualMoney

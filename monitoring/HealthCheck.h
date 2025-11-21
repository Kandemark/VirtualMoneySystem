/**
 * @file HealthCheck.h
 * @brief System health monitoring endpoint
 */

#ifndef HEALTH_CHECK_H
#define HEALTH_CHECK_H

#include <string>
#include <map>

namespace VirtualMoney {

struct HealthStatus {
    std::string status;
    std::string version;
    double uptime;
    std::map<std::string, std::string> services;
    long long timestamp;
};

class HealthCheck {
public:
    HealthCheck();
    
    /**
     * @brief Get overall system health
     */
    HealthStatus getHealth();
    
    /**
     * @brief Check specific service health
     */
    bool checkService(const std::string& serviceName);
    
    /**
     * @brief Get detailed health report
     */
    std::string getDetailedReport();
    
private:
    long long startTime;
    
    bool checkDatabase();
    bool checkCache();
    bool checkQueue();
    bool checkAPI();
    double calculateUptime();
};

} // namespace VirtualMoney

#endif

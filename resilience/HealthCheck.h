/**
 * @file HealthCheck.h
 * @brief System health monitoring
 */

#ifndef HEALTH_CHECK_H
#define HEALTH_CHECK_H

#include <string>
#include <map>

enum class HealthStatus { HEALTHY, DEGRADED, UNHEALTHY };

class HealthCheck {
public:
    HealthStatus checkService(const std::string& serviceName);
    void registerService(const std::string& serviceName);
    std::map<std::string, HealthStatus> checkAll();
private:
    std::map<std::string, HealthStatus> serviceHealth;
};

#endif

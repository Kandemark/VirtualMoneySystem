#include "HealthCheck.h"

HealthStatus HealthCheck::checkService(const std::string& serviceName) {
    auto it = serviceHealth.find(serviceName);
    return (it != serviceHealth.end()) ? it->second : HealthStatus::HEALTHY;
}

void HealthCheck::registerService(const std::string& serviceName) {
    serviceHealth[serviceName] = HealthStatus::HEALTHY;
}

std::map<std::string, HealthStatus> HealthCheck::checkAll() {
    return serviceHealth;
}

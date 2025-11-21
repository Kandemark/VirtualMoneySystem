/**
 * @file HealthChecker.h
 * @brief System health checking
 */

#ifndef HEALTH_CHECKER_H
#define HEALTH_CHECKER_H

#include <string>

class HealthChecker {
public:
    bool checkHealth();
    std::string getHealthStatus();
    void runDiagnostics();
};

#endif

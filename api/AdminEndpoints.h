/**
 * @file AdminEndpoints.h
 * @brief Admin API endpoints
 */

#ifndef ADMIN_ENDPOINTS_H
#define ADMIN_ENDPOINTS_H

#include <string>

class AdminEndpoints {
public:
    void registerRoutes();
    std::string getUserList();
    std::string suspendUser(const std::string& userId);
    std::string getSystemStats();
    std::string configureSettings(const std::string& settings);
};

#endif

/**
 * @file AdminEndpoints.cpp
 */

#include "AdminEndpoints.h"
#include <iostream>

namespace VirtualMoney {

AdminEndpoints::AdminEndpoints() {}

std::string AdminEndpoints::getSystemStats() {
    return "{\"users\": 10000, \"transactions\": 500000, \"uptime\": \"99.9%\"}";
}

std::string AdminEndpoints::getAllUsers() {
    return "[{\"id\": \"user1\", \"email\": \"user1@example.com\"}]";
}

bool AdminEndpoints::suspendUser(const std::string& userId) {
    std::cout << "User suspended: " << userId << std::endl;
    return true;
}

bool AdminEndpoints::unsuspendUser(const std::string& userId) {
    std::cout << "User unsuspended: " << userId << std::endl;
    return true;
}

std::string AdminEndpoints::getAuditLog() {
    return "[{\"action\": \"login\", \"user\": \"admin\", \"timestamp\": \"2025-11-21T15:00:00Z\"}]";
}

} // namespace VirtualMoney

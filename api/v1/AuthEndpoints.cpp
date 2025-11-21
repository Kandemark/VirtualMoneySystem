/**
 * @file AuthEndpoints.cpp (v1)
 */

#include "AuthEndpoints.h"
#include <iostream>

namespace VirtualMoney {
namespace API {
namespace V1 {

std::string login(const std::string& email, const std::string& password) {
    std::cout << "API v1: Login - " << email << std::endl;
    return "{\"token\": \"v1_token_abc123\", \"expires\": 3600}";
}

std::string register_(const std::string& email, const std::string& password) {
    std::cout << "API v1: Register - " << email << std::endl;
    return "{\"userId\": \"user_123\", \"status\": \"created\"}";
}

bool logout(const std::string& token) {
    std::cout << "API v1: Logout" << std::endl;
    return true;
}

} // namespace V1
} // namespace API
} // namespace VirtualMoney

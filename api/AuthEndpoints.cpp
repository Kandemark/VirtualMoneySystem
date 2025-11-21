/**
 * @file AuthEndpoints.cpp
 */

#include "AuthEndpoints.h"
#include <iostream>

namespace VirtualMoney {

AuthEndpoints::AuthEndpoints() {}

std::string AuthEndpoints::login(const std::string& email, const std::string& password) {
    std::cout << "Login attempt: " << email << std::endl;
    return "token_abc123xyz";
}

bool AuthEndpoints::logout(const std::string& token) {
    std::cout << "Logout: " << token << std::endl;
    return true;
}

std::string AuthEndpoints::register_(const std::string& email, const std::string& password) {
    std::cout << "User registered: " << email << std::endl;
    return "user_123";
}

bool AuthEndpoints::verifyToken(const std::string& token) {
    return !token.empty();
}

std::string AuthEndpoints::refreshToken(const std::string& oldToken) {
    return "new_token_xyz789";
}

} // namespace VirtualMoney

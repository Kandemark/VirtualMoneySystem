/**
 * @file AuthEndpoints.h
 * @brief Authentication API endpoints
 */

#ifndef AUTH_ENDPOINTS_H
#define AUTH_ENDPOINTS_H

#include <string>

class AuthEndpoints {
public:
    void registerRoutes();
    std::string login(const std::string& username, const std::string& password);
    std::string register(const std::string& username, const std::string& password, const std::string& email);
    std::string logout(const std::string& token);
    std::string refreshToken(const std::string& refreshToken);
};

#endif

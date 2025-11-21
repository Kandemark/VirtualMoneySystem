/**
 * @file AuthEndpoints.h
 * @brief API v1 authentication endpoints
 */

#ifndef AUTH_ENDPOINTS_V1_H
#define AUTH_ENDPOINTS_V1_H

#include <string>

namespace api {
namespace v1 {

class AuthEndpoints {
public:
    void registerRoutes();
    std::string login(const std::string& credentials);
    std::string logout(const std::string& token);
};

}
}

#endif

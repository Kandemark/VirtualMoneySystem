/**
 * @file Gateway.cpp
 */

#include "Gateway.h"
#include <iostream>

namespace VirtualMoney {

Gateway::Gateway() {}

std::string Gateway::routeRequest(const std::string& path, const std::string& method) {
    std::cout << "Routing: " << method << " " << path << std::endl;
    
    if (path.find("/wallet") != std::string::npos) {
        return "wallet_service";
    } else if (path.find("/transaction") != std::string::npos) {
        return "transaction_service";
    } else if (path.find("/admin") != std::string::npos) {
        return "admin_service";
    }
    
    return "unknown_service";
}

bool Gateway::authenticate(const std::string& token) {
    return !token.empty();
}

void Gateway::logRequest(const std::string& path, const std::string& method) {
    std::cout << "Request logged: " << method << " " << path << std::endl;
}

} // namespace VirtualMoney

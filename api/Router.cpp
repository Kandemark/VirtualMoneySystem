/**
 * @file Router.cpp
 */

#include "Router.h"
#include <iostream>

namespace VirtualMoney {

Router::Router() {}

void Router::addRoute(const std::string& path, const std::string& method, RouteHandler handler) {
    routes[path + "_" + method] = handler;
    std::cout << "Route added: " << method << " " << path << std::endl;
}

std::string Router::handleRequest(const std::string& path, const std::string& method) {
    std::string key = path + "_" + method;
    auto it = routes.find(key);
    
    if (it != routes.end()) {
        return it->second();
    }
    
    return "{\"error\": \"Not found\"}";
}

} // namespace VirtualMoney

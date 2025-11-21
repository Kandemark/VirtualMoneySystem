/**
 * @file Router.h
 * @brief API routing
 */

#ifndef ROUTER_H
#define ROUTER_H

#include <string>
#include <map>
#include <functional>

class Router {
public:
    void addRoute(const std::string& method, const std::string& path, std::function<std::string(const std::string&)> handler);
    std::string route(const std::string& method, const std::string& path, const std::string& body);
    void removeRoute(const std::string& method, const std::string& path);

private:
    std::map<std::string, std::function<std::string(const std::string&)>> routes;
};

#endif

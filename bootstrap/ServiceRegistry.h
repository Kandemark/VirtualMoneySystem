/**
 * @file ServiceRegistry.h
 * @brief Service registry and discovery
 */

#ifndef SERVICE_REGISTRY_H
#define SERVICE_REGISTRY_H

#include <string>
#include <map>

class ServiceRegistry {
public:
    void registerService(const std::string& serviceName, const std::string& endpoint);
    std::string getService(const std::string& serviceName);
    void unregisterService(const std::string& serviceName);
    std::map<std::string, std::string> getAllServices();
};

#endif

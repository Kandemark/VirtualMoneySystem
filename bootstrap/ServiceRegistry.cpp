#include "ServiceRegistry.h"

std::map<std::string, std::string> g_services;

void ServiceRegistry::registerService(const std::string& serviceName, const std::string& endpoint) { g_services[serviceName] = endpoint; }
std::string ServiceRegistry::getService(const std::string& serviceName) { return g_services.count(serviceName)?g_services[serviceName]:""; }
void ServiceRegistry::unregisterService(const std::string& serviceName) { g_services.erase(serviceName); }
std::map<std::string, std::string> ServiceRegistry::getAllServices() { return g_services; }

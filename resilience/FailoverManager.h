/**
 * @file FailoverManager.h
 * @brief Automatic failover to backup systems
 */

#ifndef FAILOVER_MANAGER_H
#define FAILOVER_MANAGER_H

#include <string>
#include <vector>
#include <map>

class FailoverManager {
public:
    void registerPrimary(const std::string& serviceId, const std::string& endpoint);
    void registerBackup(const std::string& serviceId, const std::string& endpoint);
    std::string getActiveEndpoint(const std::string& serviceId);
    bool triggerFailover(const std::string& serviceId);
private:
    std::map<std::string, std::string> primaryEndpoints;
    std::map<std::string, std::vector<std::string>> backupEndpoints;
    std::map<std::string, bool> isFailedOver;
};

#endif

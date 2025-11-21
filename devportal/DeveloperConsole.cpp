/**
 * @file DeveloperConsole.cpp
 * @brief Developer console implementation
 */

#include "DeveloperConsole.h"
#include <iostream>
#include <sstream>
#include <random>

namespace VirtualMoney {

DeveloperConsole::DeveloperConsole() {}

std::string DeveloperConsole::createAPIKey(const std::string& developerId, const std::string& appName) {
    APIKey key;
    key.keyId = generateKeyId();
    key.developerId = developerId;
    key.appName = appName;
    key.key = generateAPIKey();
    key.secret = generateSecret();
    key.active = true;
    key.createdAt = std::time(nullptr);
    key.rateLimit = 1000; // 1000 requests/minute
    
    apiKeys[key.keyId] = key;
    
    std::cout << "API Key created for " << appName << std::endl;
    std::cout << "Key ID: " << key.keyId << std::endl;
    std::cout << "API Key: " << key.key << std::endl;
    std::cout << "Secret: " << key.secret << std::endl;
    
    return key.keyId;
}

bool DeveloperConsole::validateAPIKey(const std::string& apiKey) {
    for (const auto& [id, key] : apiKeys) {
        if (key.key == apiKey && key.active) {
            return true;
        }
    }
    return false;
}

bool DeveloperConsole::revokeAPIKey(const std::string& keyId) {
    auto it = apiKeys.find(keyId);
    if (it != apiKeys.end()) {
        it->second.active = false;
        std::cout << "API Key revoked: " << keyId << std::endl;
        return true;
    }
    return false;
}

std::vector<APIKey> DeveloperConsole::getDeveloperKeys(const std::string& developerId) {
    std::vector<APIKey> keys;
    
    for (const auto& [id, key] : apiKeys) {
        if (key.developerId == developerId) {
            keys.push_back(key);
        }
    }
    
    return keys;
}

DeveloperConsole::UsageStats DeveloperConsole::getUsageStats(const std::string& keyId) {
    UsageStats stats;
    stats.totalRequests = 15000;
    stats.successfulRequests = 14850;
    stats.failedRequests = 150;
    stats.averageLatency = 45.5;
    stats.bandwidthUsed = 1024.0 * 1024.0 * 500.0; // 500 MB
    
    return stats;
}

std::string DeveloperConsole::generateKeyId() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(100000, 999999);
    
    std::stringstream ss;
    ss << "KEY_" << dis(gen);
    return ss.str();
}

std::string DeveloperConsole::generateAPIKey() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 15);
    
    std::stringstream ss;
    ss << "vms_";
    
    const char* hex = "0123456789abcdef";
    for (int i = 0; i < 32; ++i) {
        ss << hex[dis(gen)];
    }
    
    return ss.str();
}

std::string DeveloperConsole::generateSecret() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 15);
    
    std::stringstream ss;
    
    const char* hex = "0123456789abcdef";
    for (int i = 0; i < 64; ++i) {
        ss << hex[dis(gen)];
    }
    
    return ss.str();
}

} // namespace VirtualMoney

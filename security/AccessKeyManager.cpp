#include "AccessKeyManager.h"
#include <random>

std::string AccessKeyManager::generateAPIKey(const std::string& userId) {
    std::string key = generateRandomKey();
    APIKey apiKey;
    apiKey.key = key;
    apiKey.userId = userId;
    apiKey.createdAt = std::chrono::system_clock::now();
    apiKey.expiresAt = apiKey.createdAt + std::chrono::hours(24 * 365);
    apiKey.isActive = true;
    apiKeys[key] = apiKey;
    return key;
}

bool AccessKeyManager::validateAPIKey(const std::string& apiKey) {
    auto it = apiKeys.find(apiKey);
    if (it == apiKeys.end()) return false;
    if (!it->second.isActive) return false;
    return std::chrono::system_clock::now() < it->second.expiresAt;
}

void AccessKeyManager::revokeAPIKey(const std::string& apiKey) {
    auto it = apiKeys.find(apiKey);
    if (it != apiKeys.end()) {
        it->second.isActive = false;
    }
}

void AccessKeyManager::rotateAPIKey(const std::string& oldKey, std::string& newKey) {
    auto it = apiKeys.find(oldKey);
    if (it != apiKeys.end()) {
        std::string userId = it->second.userId;
        revokeAPIKey(oldKey);
        newKey = generateAPIKey(userId);
    }
}

std::string AccessKeyManager::generateRandomKey() const {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 15);
    const char* hex = "0123456789abcdef";
    std::string key = "sk_";
    for (int i = 0; i < 32; i++) key += hex[dis(gen)];
    return key;
}

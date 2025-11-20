#ifndef ACCESS_KEY_MANAGER_H
#define ACCESS_KEY_MANAGER_H
#include <string>
#include <map>
#include <chrono>

struct APIKey {
    std::string key;
    std::string userId;
    std::chrono::system_clock::time_point createdAt;
    std::chrono::system_clock::time_point expiresAt;
    bool isActive;
};

class AccessKeyManager {
public:
    std::string generateAPIKey(const std::string& userId);
    bool validateAPIKey(const std::string& apiKey);
    void revokeAPIKey(const std::string& apiKey);
    void rotateAPIKey(const std::string& oldKey, std::string& newKey);
private:
    std::map<std::string, APIKey> apiKeys;
    std::string generateRandomKey() const;
};

#endif

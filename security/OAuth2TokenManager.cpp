#include "OAuth2TokenManager.h"
#include <random>

OAuth2Token OAuth2TokenManager::generateToken(const std::string& clientId, const std::string& scope) {
    OAuth2Token token;
    token.accessToken = generateRandomToken();
    token.refreshToken = generateRandomToken();
    token.expiresAt = std::chrono::system_clock::now() + std::chrono::hours(1);
    token.scope = scope;
    tokens[token.accessToken] = token;
    return token;
}

bool OAuth2TokenManager::validateToken(const std::string& accessToken) {
    auto it = tokens.find(accessToken);
    if (it == tokens.end()) return false;
    return std::chrono::system_clock::now() < it->second.expiresAt;
}

OAuth2Token OAuth2TokenManager::refreshToken(const std::string& refreshToken) {
    for (const auto& [key, token] : tokens) {
        if (token.refreshToken == refreshToken) {
            return generateToken("client", token.scope);
        }
    }
    throw std::runtime_error("Invalid refresh token");
}

void OAuth2TokenManager::revokeToken(const std::string& accessToken) {
    tokens.erase(accessToken);
}

std::string OAuth2TokenManager::generateRandomToken() const {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 15);
    const char* hex = "0123456789abcdef";
    std::string token;
    for (int i = 0; i < 64; i++) token += hex[dis(gen)];
    return token;
}

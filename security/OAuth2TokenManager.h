#ifndef OAUTH2_TOKEN_MANAGER_H
#define OAUTH2_TOKEN_MANAGER_H
#include <string>
#include <map>
#include <chrono>

struct OAuth2Token {
    std::string accessToken;
    std::string refreshToken;
    std::chrono::system_clock::time_point expiresAt;
    std::string scope;
};

class OAuth2TokenManager {
public:
    OAuth2Token generateToken(const std::string& clientId, const std::string& scope);
    bool validateToken(const std::string& accessToken);
    OAuth2Token refreshToken(const std::string& refreshToken);
    void revokeToken(const std::string& accessToken);
private:
    std::map<std::string, OAuth2Token> tokens;
    std::string generateRandomToken() const;
};

#endif

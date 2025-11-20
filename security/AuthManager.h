#ifndef AUTH_MANAGER_H
#define AUTH_MANAGER_H
#include <string>
#include <map>

class AuthManager {
public:
    bool authenticate(const std::string& userId, const std::string& password);
    bool authorize(const std::string& userId, const std::string& action);
    void grantPermission(const std::string& userId, const std::string& action);
    void revokePermission(const std::string& userId, const std::string& action);
private:
    std::map<std::string, std::string> credentials;
    std::map<std::string, std::set<std::string>> permissions;
};

#endif

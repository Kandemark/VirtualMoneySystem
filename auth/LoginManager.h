#ifndef LOGIN_MANAGER_H
#define LOGIN_MANAGER_H

#include <string>
#include <map>
#include <chrono>

struct LoginAttempt {
    std::string userId;
    std::chrono::system_clock::time_point timestamp;
    bool successful;
    std::string ipAddress;
};

class LoginManager {
public:
    LoginManager(int maxAttempts = 5, int lockoutMinutes = 15);

    bool attemptLogin(const std::string& userId, const std::string& password, const std::string& ipAddress);
    bool isAccountLocked(const std::string& userId) const;
    void unlockAccount(const std::string& userId);
    std::vector<LoginAttempt> getLoginHistory(const std::string& userId) const;

private:
    std::map<std::string, std::string> userPasswords; // userId -> hashedPassword
    std::map<std::string, std::vector<LoginAttempt>> loginAttempts;
    std::map<std::string, std::chrono::system_clock::time_point> accountLockouts;
    int maxAttempts;
    int lockoutMinutes;
    
    bool verifyPassword(const std::string& password, const std::string& hashedPassword) const;
    void recordAttempt(const std::string& userId, bool successful, const std::string& ipAddress);
};

#endif // LOGIN_MANAGER_H

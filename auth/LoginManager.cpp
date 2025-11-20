#include "LoginManager.h"
#include <iostream>

LoginManager::LoginManager(int maxAttempts, int lockoutMinutes)
    : maxAttempts(maxAttempts), lockoutMinutes(lockoutMinutes) {
    // Initialize with some test users
    userPasswords["admin"] = "hashed_admin_password";
    userPasswords["user1"] = "hashed_user1_password";
}

bool LoginManager::attemptLogin(const std::string& userId, const std::string& password, const std::string& ipAddress) {
    // Check if account is locked
    if (isAccountLocked(userId)) {
        std::cout << "[LoginManager] Account locked: " << userId << std::endl;
        return false;
    }
    
    // Check if user exists
    auto it = userPasswords.find(userId);
    if (it == userPasswords.end()) {
        recordAttempt(userId, false, ipAddress);
        return false;
    }
    
    // Verify password
    bool success = verifyPassword(password, it->second);
    recordAttempt(userId, success, ipAddress);
    
    if (success) {
        // Clear failed attempts on successful login
        loginAttempts[userId].clear();
        std::cout << "[LoginManager] Login successful: " << userId << std::endl;
    } else {
        // Check if we should lock the account
        auto& attempts = loginAttempts[userId];
        int recentFailures = 0;
        auto now = std::chrono::system_clock::now();
        auto cutoff = now - std::chrono::minutes(lockoutMinutes);
        
        for (const auto& attempt : attempts) {
            if (!attempt.successful && attempt.timestamp > cutoff) {
                recentFailures++;
            }
        }
        
        if (recentFailures >= maxAttempts) {
            accountLockouts[userId] = now + std::chrono::minutes(lockoutMinutes);
            std::cout << "[LoginManager] Account locked due to failed attempts: " << userId << std::endl;
        }
    }
    
    return success;
}

bool LoginManager::isAccountLocked(const std::string& userId) const {
    auto it = accountLockouts.find(userId);
    if (it == accountLockouts.end()) {
        return false;
    }
    
    return std::chrono::system_clock::now() < it->second;
}

void LoginManager::unlockAccount(const std::string& userId) {
    accountLockouts.erase(userId);
    loginAttempts[userId].clear();
    std::cout << "[LoginManager] Account unlocked: " << userId << std::endl;
}

std::vector<LoginAttempt> LoginManager::getLoginHistory(const std::string& userId) const {
    auto it = loginAttempts.find(userId);
    if (it == loginAttempts.end()) {
        return {};
    }
    return it->second;
}

bool LoginManager::verifyPassword(const std::string& password, const std::string& hashedPassword) const {
    // Simplified password verification (in real system, use proper hashing)
    return "hashed_" + password == hashedPassword;
}

void LoginManager::recordAttempt(const std::string& userId, bool successful, const std::string& ipAddress) {
    LoginAttempt attempt;
    attempt.userId = userId;
    attempt.timestamp = std::chrono::system_clock::now();
    attempt.successful = successful;
    attempt.ipAddress = ipAddress;
    
    loginAttempts[userId].push_back(attempt);
}

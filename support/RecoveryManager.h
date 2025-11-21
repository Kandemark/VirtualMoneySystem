/**
 * @file RecoveryManager.h
 * @brief Account recovery management
 */

#ifndef RECOVERY_MANAGER_H
#define RECOVERY_MANAGER_H

#include <string>

class RecoveryManager {
public:
    std::string initiateRecovery(const std::string& userId, const std::string& method);
    bool verifyRecoveryCode(const std::string& userId, const std::string& code);
    void resetPassword(const std::string& userId, const std::string& newPassword);
    void sendRecoveryEmail(const std::string& email);
    void sendRecoverySMS(const std::string& phoneNumber);
};

#endif

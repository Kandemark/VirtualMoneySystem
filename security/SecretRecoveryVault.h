#ifndef SECRET_RECOVERY_VAULT_H
#define SECRET_RECOVERY_VAULT_H
#include <string>
#include <map>

class SecretRecoveryVault {
public:
    void storeRecoveryCode(const std::string& userId, const std::string& recoveryCode);
    bool validateRecoveryCode(const std::string& userId, const std::string& recoveryCode);
    std::string generateRecoveryCode(const std::string& userId);
private:
    std::map<std::string, std::string> recoveryCodes;
    std::string generateRandomCode() const;
};

#endif

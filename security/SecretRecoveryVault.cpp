#include "SecretRecoveryVault.h"
#include <random>

void SecretRecoveryVault::storeRecoveryCode(const std::string& userId, const std::string& recoveryCode) {
    recoveryCodes[userId] = recoveryCode;
}

bool SecretRecoveryVault::validateRecoveryCode(const std::string& userId, const std::string& recoveryCode) {
    auto it = recoveryCodes.find(userId);
    if (it != recoveryCodes.end()) {
        return it->second == recoveryCode;
    }
    return false;
}

std::string SecretRecoveryVault::generateRecoveryCode(const std::string& userId) {
    std::string code = generateRandomCode();
    storeRecoveryCode(userId, code);
    return code;
}

std::string SecretRecoveryVault::generateRandomCode() const {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 35);
    const char* chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::string code;
    for (int i = 0; i < 16; i++) {
        code += chars[dis(gen)];
        if ((i + 1) % 4 == 0 && i < 15) code += "-";
    }
    return code;
}

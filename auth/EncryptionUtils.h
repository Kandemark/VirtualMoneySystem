#ifndef ENCRYPTION_UTILS_H
#define ENCRYPTION_UTILS_H

#include <string>

class EncryptionUtils {
public:
    static std::string hashPassword(const std::string& password, const std::string& salt = "");
    static std::string generateSalt();
    static bool verifyPassword(const std::string& password, const std::string& hashedPassword, const std::string& salt = "");
    static std::string encrypt(const std::string& plaintext, const std::string& key);
    static std::string decrypt(const std::string& ciphertext, const std::string& key);
    static std::string generateToken(int length = 32);
};

#endif // ENCRYPTION_UTILS_H

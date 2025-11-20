#ifndef ENCRYPTION_UTILS_SEC_H
#define ENCRYPTION_UTILS_SEC_H
#include <string>

class EncryptionUtilsSec {
public:
    static std::string encryptAES(const std::string& plaintext, const std::string& key);
    static std::string decryptAES(const std::string& ciphertext, const std::string& key);
    static std::string encryptRSA(const std::string& plaintext, const std::string& publicKey);
    static std::string decryptRSA(const std::string& ciphertext, const std::string& privateKey);
};

#endif

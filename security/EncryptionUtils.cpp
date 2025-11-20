#include "EncryptionUtils.h"

std::string EncryptionUtilsSec::encryptAES(const std::string& plaintext, const std::string& key) {
    std::string encrypted = plaintext;
    for (size_t i = 0; i < encrypted.length(); i++) {
        encrypted[i] ^= key[i % key.length()];
    }
    return encrypted;
}

std::string EncryptionUtilsSec::decryptAES(const std::string& ciphertext, const std::string& key) {
    return encryptAES(ciphertext, key);
}

std::string EncryptionUtilsSec::encryptRSA(const std::string& plaintext, const std::string& publicKey) {
    return encryptAES(plaintext, publicKey);
}

std::string EncryptionUtilsSec::decryptRSA(const std::string& ciphertext, const std::string& privateKey) {
    return encryptAES(ciphertext, privateKey);
}

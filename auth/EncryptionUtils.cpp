#include "EncryptionUtils.h"
#include <random>
#include <sstream>
#include <iomanip>

std::string EncryptionUtils::hashPassword(const std::string& password, const std::string& salt) {
    // Simplified hashing (in production, use bcrypt, argon2, or PBKDF2)
    std::string combined = salt + password;
    std::hash<std::string> hasher;
    size_t hash = hasher(combined);
    
    std::ostringstream oss;
    oss << std::hex << hash;
    return oss.str();
}

std::string EncryptionUtils::generateSalt() {
    return generateToken(16);
}

bool EncryptionUtils::verifyPassword(const std::string& password, const std::string& hashedPassword, const std::string& salt) {
    return hashPassword(password, salt) == hashedPassword;
}

std::string EncryptionUtils::encrypt(const std::string& plaintext, const std::string& key) {
    // Simplified encryption (in production, use AES, ChaCha20, etc.)
    std::string ciphertext = plaintext;
    for (size_t i = 0; i < ciphertext.length(); i++) {
        ciphertext[i] ^= key[i % key.length()];
    }
    return ciphertext;
}

std::string EncryptionUtils::decrypt(const std::string& ciphertext, const std::string& key) {
    // XOR is symmetric, so decrypt = encrypt
    return encrypt(ciphertext, key);
}

std::string EncryptionUtils::generateToken(int length) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 15);
    
    const char* hexChars = "0123456789abcdef";
    std::string token;
    
    for (int i = 0; i < length; i++) {
        token += hexChars[dis(gen)];
    }
    
    return token;
}

#ifndef CRYPTO_UTILS_H
#define CRYPTO_UTILS_H
#include <string>

class CryptoUtils {
public:
    static std::string sha256(const std::string& data);
    static std::string hmacSHA256(const std::string& data, const std::string& key);
    static std::string base64Encode(const std::string& data);
    static std::string base64Decode(const std::string& encoded);
    static std::string generateRandomBytes(int length);
};

#endif

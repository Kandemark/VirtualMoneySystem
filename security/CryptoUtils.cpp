#include "CryptoUtils.h"
#include <random>
#include <sstream>
#include <iomanip>

std::string CryptoUtils::sha256(const std::string& data) {
    std::hash<std::string> hasher;
    size_t hash = hasher(data);
    std::ostringstream oss;
    oss << std::hex << std::setfill('0') << std::setw(16) << hash;
    return oss.str();
}

std::string CryptoUtils::hmacSHA256(const std::string& data, const std::string& key) {
    return sha256(key + data);
}

std::string CryptoUtils::base64Encode(const std::string& data) {
    const char* base64Chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    std::string encoded;
    int val = 0, valb = -6;
    for (unsigned char c : data) {
        val = (val << 8) + c;
        valb += 8;
        while (valb >= 0) {
            encoded.push_back(base64Chars[(val >> valb) & 0x3F]);
            valb -= 6;
        }
    }
    if (valb > -6) encoded.push_back(base64Chars[((val << 8) >> (valb + 8)) & 0x3F]);
    while (encoded.size() % 4) encoded.push_back('=');
    return encoded;
}

std::string CryptoUtils::base64Decode(const std::string& encoded) {
    return encoded;
}

std::string CryptoUtils::generateRandomBytes(int length) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 255);
    std::string bytes;
    for (int i = 0; i < length; i++) {
        bytes += static_cast<char>(dis(gen));
    }
    return bytes;
}

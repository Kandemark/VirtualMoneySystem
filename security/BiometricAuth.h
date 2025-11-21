/**
 * @file BiometricAuth.h
 * @brief Biometric authentication system
 */

#ifndef BIOMETRIC_AUTH_H
#define BIOMETRIC_AUTH_H

#include <string>
#include <vector>
#include <map>

namespace VirtualMoney {

enum class BiometricType {
    FINGERPRINT,
    FACE,
    VOICE,
    IRIS,
    BEHAVIORAL
};

struct BiometricTemplate {
    BiometricType type;
    std::vector<uint8_t> data;
    double quality; // 0.0 to 1.0
    std::time_t enrolledAt;
};

struct BiometricVerification {
    bool verified;
    double confidence;
    BiometricType type;
    std::string failureReason;
};

class BiometricAuth {
public:
    BiometricAuth();
    
    /**
     * @brief Enroll biometric template
     */
    bool enrollBiometric(const std::string& userId, BiometricType type, const std::vector<uint8_t>& data);
    
    /**
     * @brief Verify fingerprint
     */
    BiometricVerification verifyFingerprint(const std::string& userId, const std::vector<uint8_t>& fingerprint);
    
    /**
     * @brief Verify face
     */
    BiometricVerification verifyFace(const std::string& userId, const std::vector<uint8_t>& faceImage);
    
    /**
     * @brief Verify voice
     */
    BiometricVerification verifyVoice(const std::string& userId, const std::vector<uint8_t>& voiceSample);
    
    /**
     * @brief Multi-factor biometric verification
     */
    bool verifyMultiFactor(const std::string& userId, const std::vector<BiometricType>& types);
    
    /**
     * @brief Liveness detection
     */
    bool detectLiveness(const std::vector<uint8_t>& biometricData, BiometricType type);
    
    /**
     * @brief Anti-spoofing check
     */
    bool checkAntiSpoofing(const std::vector<uint8_t>& data);
    
    /**
     * @brief Get enrolled biometrics
     */
    std::vector<BiometricType> getEnrolledBiometrics(const std::string& userId);
    
    /**
     * @brief Remove biometric
     */
    bool removeBiometric(const std::string& userId, BiometricType type);
    
private:
    std::map<std::string, std::vector<BiometricTemplate>> userBiometrics;
    
    double compareFingerprints(const std::vector<uint8_t>& template1, const std::vector<uint8_t>& template2);
    double compareFaces(const std::vector<uint8_t>& template1, const std::vector<uint8_t>& template2);
    double compareVoices(const std::vector<uint8_t>& template1, const std::vector<uint8_t>& template2);
    double calculateQuality(const std::vector<uint8_t>& data, BiometricType type);
};

} // namespace VirtualMoney

#endif

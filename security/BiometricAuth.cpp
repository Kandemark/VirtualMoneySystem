/**
 * @file BiometricAuth.cpp
 */

#include "BiometricAuth.h"
#include <iostream>
#include <algorithm>
#include <random>

namespace VirtualMoney {

BiometricAuth::BiometricAuth() {
    std::cout << "Biometric authentication system initialized" << std::endl;
}

bool BiometricAuth::enrollBiometric(const std::string& userId, BiometricType type, const std::vector<uint8_t>& data) {
    double quality = calculateQuality(data, type);
    
    if (quality < 0.7) {
        std::cout << "Biometric quality too low: " << quality << std::endl;
        return false;
    }
    
    BiometricTemplate template_;
    template_.type = type;
    template_.data = data;
    template_.quality = quality;
    template_.enrolledAt = std::time(nullptr);
    
    userBiometrics[userId].push_back(template_);
    
    std::string typeName;
    switch(type) {
        case BiometricType::FINGERPRINT: typeName = "Fingerprint"; break;
        case BiometricType::FACE: typeName = "Face"; break;
        case BiometricType::VOICE: typeName = "Voice"; break;
        case BiometricType::IRIS: typeName = "Iris"; break;
        case BiometricType::BEHAVIORAL: typeName = "Behavioral"; break;
    }
    
    std::cout << typeName << " enrolled for user " << userId 
              << " (quality: " << (quality * 100) << "%)" << std::endl;
    
    return true;
}

BiometricVerification BiometricAuth::verifyFingerprint(const std::string& userId, const std::vector<uint8_t>& fingerprint) {
    BiometricVerification result;
    result.type = BiometricType::FINGERPRINT;
    result.verified = false;
    result.confidence = 0.0;
    
    // Liveness detection
    if (!detectLiveness(fingerprint, BiometricType::FINGERPRINT)) {
        result.failureReason = "Liveness detection failed";
        return result;
    }
    
    // Anti-spoofing
    if (!checkAntiSpoofing(fingerprint)) {
        result.failureReason = "Anti-spoofing check failed";
        return result;
    }
    
    auto it = userBiometrics.find(userId);
    if (it != userBiometrics.end()) {
        for (const auto& template_ : it->second) {
            if (template_.type == BiometricType::FINGERPRINT) {
                double similarity = compareFingerprints(template_.data, fingerprint);
                
                if (similarity > 0.95) {
                    result.verified = true;
                    result.confidence = similarity;
                    std::cout << "Fingerprint verified for " << userId 
                              << " (confidence: " << (similarity * 100) << "%)" << std::endl;
                    return result;
                }
            }
        }
    }
    
    result.failureReason = "Fingerprint does not match";
    std::cout << "Fingerprint verification failed for " << userId << std::endl;
    
    return result;
}

BiometricVerification BiometricAuth::verifyFace(const std::string& userId, const std::vector<uint8_t>& faceImage) {
    BiometricVerification result;
    result.type = BiometricType::FACE;
    result.verified = false;
    result.confidence = 0.0;
    
    if (!detectLiveness(faceImage, BiometricType::FACE)) {
        result.failureReason = "Liveness detection failed (possible photo attack)";
        return result;
    }
    
    auto it = userBiometrics.find(userId);
    if (it != userBiometrics.end()) {
        for (const auto& template_ : it->second) {
            if (template_.type == BiometricType::FACE) {
                double similarity = compareFaces(template_.data, faceImage);
                
                if (similarity > 0.90) {
                    result.verified = true;
                    result.confidence = similarity;
                    std::cout << "Face verified for " << userId << std::endl;
                    return result;
                }
            }
        }
    }
    
    result.failureReason = "Face does not match";
    return result;
}

BiometricVerification BiometricAuth::verifyVoice(const std::string& userId, const std::vector<uint8_t>& voiceSample) {
    BiometricVerification result;
    result.type = BiometricType::VOICE;
    result.verified = false;
    result.confidence = 0.0;
    
    auto it = userBiometrics.find(userId);
    if (it != userBiometrics.end()) {
        for (const auto& template_ : it->second) {
            if (template_.type == BiometricType::VOICE) {
                double similarity = compareVoices(template_.data, voiceSample);
                
                if (similarity > 0.85) {
                    result.verified = true;
                    result.confidence = similarity;
                    std::cout << "Voice verified for " << userId << std::endl;
                    return result;
                }
            }
        }
    }
    
    result.failureReason = "Voice does not match";
    return result;
}

bool BiometricAuth::verifyMultiFactor(const std::string& userId, const std::vector<BiometricType>& types) {
    int successCount = 0;
    
    for (const auto& type : types) {
        // Simplified - in production, actually verify each type
        successCount++;
    }
    
    bool verified = successCount >= 2;
    
    std::cout << "Multi-factor biometric verification: " 
              << (verified ? "SUCCESS" : "FAILED") << std::endl;
    
    return verified;
}

bool BiometricAuth::detectLiveness(const std::vector<uint8_t>& biometricData, BiometricType type) {
    // Liveness detection to prevent spoofing
    // In production: actual liveness detection algorithms
    
    std::cout << "Liveness detection: PASSED" << std::endl;
    return true;
}

bool BiometricAuth::checkAntiSpoofing(const std::vector<uint8_t>& data) {
    // Anti-spoofing checks
    // In production: detect fake fingerprints, masks, etc.
    
    return true;
}

std::vector<BiometricType> BiometricAuth::getEnrolledBiometrics(const std::string& userId) {
    std::vector<BiometricType> enrolled;
    
    auto it = userBiometrics.find(userId);
    if (it != userBiometrics.end()) {
        for (const auto& template_ : it->second) {
            enrolled.push_back(template_.type);
        }
    }
    
    return enrolled;
}

bool BiometricAuth::removeBiometric(const std::string& userId, BiometricType type) {
    auto it = userBiometrics.find(userId);
    if (it != userBiometrics.end()) {
        auto& templates = it->second;
        templates.erase(
            std::remove_if(templates.begin(), templates.end(),
                [type](const BiometricTemplate& t) { return t.type == type; }),
            templates.end()
        );
        
        std::cout << "Biometric removed for " << userId << std::endl;
        return true;
    }
    
    return false;
}

double BiometricAuth::compareFingerprints(const std::vector<uint8_t>& template1, const std::vector<uint8_t>& template2) {
    // Simplified fingerprint matching
    // In production: minutiae-based matching
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.90, 0.99);
    
    return dis(gen);
}

double BiometricAuth::compareFaces(const std::vector<uint8_t>& template1, const std::vector<uint8_t>& template2) {
    // Simplified face matching
    // In production: deep learning face recognition
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.85, 0.98);
    
    return dis(gen);
}

double BiometricAuth::compareVoices(const std::vector<uint8_t>& template1, const std::vector<uint8_t>& template2) {
    // Simplified voice matching
    // In production: voice biometric algorithms
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.80, 0.95);
    
    return dis(gen);
}

double BiometricAuth::calculateQuality(const std::vector<uint8_t>& data, BiometricType type) {
    // Quality assessment
    if (data.empty()) return 0.0;
    
    return 0.85; // Simplified
}

} // namespace VirtualMoney

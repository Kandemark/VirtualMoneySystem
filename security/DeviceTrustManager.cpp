#include "DeviceTrustManager.h"

int DeviceTrustManager::calculateTrustScore(const std::string& deviceId) {
    auto it = deviceScores.find(deviceId);
    if (it != deviceScores.end()) {
        return it->second;
    }
    deviceScores[deviceId] = 50;
    return 50;
}

bool DeviceTrustManager::isDeviceTrusted(const std::string& deviceId) {
    auto it = trustedDevices.find(deviceId);
    if (it != trustedDevices.end()) {
        return it->second;
    }
    return calculateTrustScore(deviceId) >= 70;
}

void DeviceTrustManager::markDeviceAsTrusted(const std::string& deviceId) {
    trustedDevices[deviceId] = true;
    deviceScores[deviceId] = 100;
}

void DeviceTrustManager::markDeviceAsUntrusted(const std::string& deviceId) {
    trustedDevices[deviceId] = false;
    deviceScores[deviceId] = 0;
}

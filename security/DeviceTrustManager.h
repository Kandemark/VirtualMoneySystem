#ifndef DEVICE_TRUST_MANAGER_H
#define DEVICE_TRUST_MANAGER_H
#include <string>
#include <map>

class DeviceTrustManager {
public:
    int calculateTrustScore(const std::string& deviceId);
    bool isDeviceTrusted(const std::string& deviceId);
    void markDeviceAsTrusted(const std::string& deviceId);
    void markDeviceAsUntrusted(const std::string& deviceId);
private:
    std::map<std::string, int> deviceScores;
    std::map<std::string, bool> trustedDevices;
};

#endif

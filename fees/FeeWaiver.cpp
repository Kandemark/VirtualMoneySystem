#include "FeeWaiver.h"

void FeeWaiver::grantWaiver(const std::string& userId, const std::string& feeType, int durationDays) {
    waivers[userId][feeType] = true;
}

bool FeeWaiver::hasWaiver(const std::string& userId, const std::string& feeType) {
    auto userIt = waivers.find(userId);
    if (userIt != waivers.end()) {
        auto feeIt = userIt->second.find(feeType);
        if (feeIt != userIt->second.end()) {
            return feeIt->second;
        }
    }
    return false;
}

void FeeWaiver::revokeWaiver(const std::string& userId, const std::string& feeType) {
    if (waivers.find(userId) != waivers.end()) {
        waivers[userId].erase(feeType);
    }
}

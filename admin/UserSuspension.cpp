#include "UserSuspension.h"

bool UserSuspension::suspendUser(const std::string& userId, const std::string& reason, int durationDays) {
    SuspensionRecord record;
    record.userId = userId;
    record.reason = reason;
    record.suspendedAt = std::chrono::system_clock::now();
    record.isPermanent = (durationDays == -1);
    if (!record.isPermanent) {
        record.expiresAt = record.suspendedAt + std::chrono::hours(24 * durationDays);
    }
    suspensions[userId] = record;
    return true;
}

bool UserSuspension::unsuspendUser(const std::string& userId) {
    return suspensions.erase(userId) > 0;
}

bool UserSuspension::isSuspended(const std::string& userId) const {
    auto it = suspensions.find(userId);
    if (it == suspensions.end()) return false;
    if (it->second.isPermanent) return true;
    return std::chrono::system_clock::now() < it->second.expiresAt;
}

SuspensionRecord UserSuspension::getSuspensionInfo(const std::string& userId) const {
    return suspensions.at(userId);
}

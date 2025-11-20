#ifndef USER_SUSPENSION_H
#define USER_SUSPENSION_H
#include <string>
#include <map>
#include <chrono>

struct SuspensionRecord {
    std::string userId;
    std::string reason;
    std::chrono::system_clock::time_point suspendedAt;
    std::chrono::system_clock::time_point expiresAt;
    bool isPermanent;
};

class UserSuspension {
public:
    bool suspendUser(const std::string& userId, const std::string& reason, int durationDays = -1);
    bool unsuspendUser(const std::string& userId);
    bool isSuspended(const std::string& userId) const;
    SuspensionRecord getSuspensionInfo(const std::string& userId) const;

private:
    std::map<std::string, SuspensionRecord> suspensions;
};

#endif

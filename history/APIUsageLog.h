/**
 * @file APIUsageLog.h
 * @brief API usage logging and analytics
 */

#ifndef API_USAGE_LOG_H
#define API_USAGE_LOG_H

#include <string>
#include <map>

class APIUsageLog {
public:
    void logAPICall(const std::string& endpoint, const std::string& userId, int responseCode);
    std::map<std::string, int> getUsageStats(const std::string& userId);
    int getRateLimitRemaining(const std::string& userId);
};

#endif

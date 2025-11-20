#ifndef RATE_LIMITER_H
#define RATE_LIMITER_H
#include <string>
#include <map>
#include <chrono>
#include <deque>

class RateLimiter {
public:
    RateLimiter(int maxRequests = 100, int windowSeconds = 60);
    bool allowRequest(const std::string& identifier);
    int getRemainingRequests(const std::string& identifier) const;
    void resetLimit(const std::string& identifier);
private:
    int maxRequests;
    int windowSeconds;
    std::map<std::string, std::deque<std::chrono::system_clock::time_point>> requestHistory;
    void cleanOldRequests(const std::string& identifier);
};

#endif

#include "RateLimiter.h"

RateLimiter::RateLimiter(int maxRequests, int windowSeconds)
    : maxRequests(maxRequests), windowSeconds(windowSeconds) {}

bool RateLimiter::allowRequest(const std::string& identifier) {
    cleanOldRequests(identifier);
    
    auto& history = requestHistory[identifier];
    if (history.size() >= static_cast<size_t>(maxRequests)) {
        return false;
    }
    
    history.push_back(std::chrono::system_clock::now());
    return true;
}

int RateLimiter::getRemainingRequests(const std::string& identifier) const {
    auto it = requestHistory.find(identifier);
    if (it == requestHistory.end()) {
        return maxRequests;
    }
    return maxRequests - it->second.size();
}

void RateLimiter::resetLimit(const std::string& identifier) {
    requestHistory.erase(identifier);
}

void RateLimiter::cleanOldRequests(const std::string& identifier) {
    auto& history = requestHistory[identifier];
    auto now = std::chrono::system_clock::now();
    auto cutoff = now - std::chrono::seconds(windowSeconds);
    
    while (!history.empty() && history.front() < cutoff) {
        history.pop_front();
    }
}

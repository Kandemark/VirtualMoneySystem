/**
 * @file RateLimitPolicies.h
 * @brief Rate limiting policy definitions
 */

#ifndef RATE_LIMIT_POLICIES_H
#define RATE_LIMIT_POLICIES_H

#include <string>
#include <map>

/**
 * @brief Rate limit policy
 */
struct RateLimitPolicy {
    int maxRequests;
    int windowSeconds;
    std::string action;  // block, throttle, warn
};

/**
 * @brief Manages rate limit policies
 */
class RateLimitPolicies {
public:
    /**
     * @brief Set rate limit policy
     * @param policyName Policy name
     * @param maxRequests Maximum requests
     * @param windowSeconds Time window in seconds
     */
    void setPolicy(const std::string& policyName, int maxRequests, int windowSeconds);
    
    /**
     * @brief Get policy
     * @param policyName Policy name
     * @return Rate limit policy
     */
    RateLimitPolicy getPolicy(const std::string& policyName);
    
    /**
     * @brief Check if request is allowed
     * @param policyName Policy name
     * @param userId User identifier
     * @return true if allowed
     */
    bool isAllowed(const std::string& policyName, const std::string& userId);

private:
    std::map<std::string, RateLimitPolicy> policies;
};

#endif

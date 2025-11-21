/**
 * @file CircuitBreaker.h
 * @brief Circuit breaker pattern for fault tolerance
 */

#ifndef CIRCUIT_BREAKER_H
#define CIRCUIT_BREAKER_H

#include <string>
#include <map>
#include <chrono>

enum class CircuitState { CLOSED, OPEN, HALF_OPEN };

class CircuitBreaker {
public:
    CircuitBreaker(int failureThreshold = 5, int timeoutSeconds = 60);
    bool allowRequest(const std::string& serviceId);
    void recordSuccess(const std::string& serviceId);
    void recordFailure(const std::string& serviceId);
    CircuitState getState(const std::string& serviceId);
private:
    int failureThreshold;
    int timeoutSeconds;
    std::map<std::string, int> failureCounts;
    std::map<std::string, CircuitState> states;
    std::map<std::string, std::chrono::system_clock::time_point> lastFailureTime;
};

#endif

#include "CircuitBreaker.h"

CircuitBreaker::CircuitBreaker(int failureThreshold, int timeoutSeconds)
    : failureThreshold(failureThreshold), timeoutSeconds(timeoutSeconds) {}

bool CircuitBreaker::allowRequest(const std::string& serviceId) {
    CircuitState state = getState(serviceId);
    
    if (state == CircuitState::OPEN) {
        auto now = std::chrono::system_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(
            now - lastFailureTime[serviceId]).count();
        
        if (elapsed >= timeoutSeconds) {
            states[serviceId] = CircuitState::HALF_OPEN;
            return true;
        }
        return false;
    }
    
    return true;
}

void CircuitBreaker::recordSuccess(const std::string& serviceId) {
    failureCounts[serviceId] = 0;
    states[serviceId] = CircuitState::CLOSED;
}

void CircuitBreaker::recordFailure(const std::string& serviceId) {
    failureCounts[serviceId]++;
    lastFailureTime[serviceId] = std::chrono::system_clock::now();
    
    if (failureCounts[serviceId] >= failureThreshold) {
        states[serviceId] = CircuitState::OPEN;
    }
}

CircuitState CircuitBreaker::getState(const std::string& serviceId) {
    auto it = states.find(serviceId);
    return (it != states.end()) ? it->second : CircuitState::CLOSED;
}

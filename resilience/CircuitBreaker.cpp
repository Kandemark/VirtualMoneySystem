/**
 * @file CircuitBreaker.cpp
 */

#include "CircuitBreaker.h"
#include <iostream>

CircuitBreaker::CircuitBreaker(int failureThreshold, int timeoutSeconds)
    : failureThreshold(failureThreshold), timeoutSeconds(timeoutSeconds) {}

bool CircuitBreaker::allowRequest(const std::string& serviceId) {
    auto stateIt = states.find(serviceId);
    
    // Initialize if not exists
    if (stateIt == states.end()) {
        states[serviceId] = CircuitState::CLOSED;
        failureCounts[serviceId] = 0;
        return true;
    }
    
    CircuitState state = stateIt->second;
    
    if (state == CircuitState::CLOSED) {
        return true;
    }
    
    if (state == CircuitState::OPEN) {
        // Check if timeout has passed
        auto now = std::chrono::system_clock::now();
        auto lastFailure = lastFailureTime[serviceId];
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - lastFailure).count();
        
        if (elapsed >= timeoutSeconds) {
            // Try half-open
            states[serviceId] = CircuitState::HALF_OPEN;
            std::cout << "Circuit breaker HALF_OPEN for " << serviceId << std::endl;
            return true;
        }
        
        std::cout << "Circuit breaker OPEN for " << serviceId << " - request rejected" << std::endl;
        return false;
    }
    
    // HALF_OPEN - allow one request to test
    return true;
}

void CircuitBreaker::recordSuccess(const std::string& serviceId) {
    auto stateIt = states.find(serviceId);
    if (stateIt != states.end()) {
        if (stateIt->second == CircuitState::HALF_OPEN) {
            // Success in half-open, close circuit
            states[serviceId] = CircuitState::CLOSED;
            failureCounts[serviceId] = 0;
            std::cout << "Circuit breaker CLOSED for " << serviceId << std::endl;
        }
    }
}

void CircuitBreaker::recordFailure(const std::string& serviceId) {
    failureCounts[serviceId]++;
    lastFailureTime[serviceId] = std::chrono::system_clock::now();
    
    if (failureCounts[serviceId] >= failureThreshold) {
        states[serviceId] = CircuitState::OPEN;
        std::cout << "Circuit breaker OPEN for " << serviceId 
                  << " (failures: " << failureCounts[serviceId] << ")" << std::endl;
    }
}

CircuitState CircuitBreaker::getState(const std::string& serviceId) {
    auto it = states.find(serviceId);
    if (it != states.end()) {
        return it->second;
    }
    return CircuitState::CLOSED;
}

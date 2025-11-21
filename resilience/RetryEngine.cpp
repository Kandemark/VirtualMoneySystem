/**
 * @file RetryEngine.cpp
 */

#include "RetryEngine.h"
#include <iostream>
#include <thread>

RetryEngine::RetryEngine() : maxRetries(3), retryDelayMs(1000) {}

bool RetryEngine::executeWithRetry(std::function<bool()> operation) {
    for (int attempt = 0; attempt < maxRetries; ++attempt) {
        if (operation()) {
            return true;
        }
        
        std::cout << "Retry attempt " << (attempt + 1) << " of " << maxRetries << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(retryDelayMs * (attempt + 1)));
    }
    
    std::cout << "All retry attempts failed" << std::endl;
    return false;
}

void RetryEngine::setMaxRetries(int retries) {
    maxRetries = retries;
}

void RetryEngine::setRetryDelay(int delayMs) {
    retryDelayMs = delayMs;
}

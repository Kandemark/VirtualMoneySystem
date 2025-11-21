/**
 * @file RetryEngine.h
 * @brief Retry mechanism for failed operations
 */

#ifndef RETRY_ENGINE_H
#define RETRY_ENGINE_H

#include <string>
#include <functional>

class RetryEngine {
public:
    bool retry(std::function<bool()> operation, int maxAttempts = 3);
    void setBackoffStrategy(const std::string& strategy);
};

#endif

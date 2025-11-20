#include "RetryQueue.h"
#include <iostream>

RetryQueue::RetryQueue(int maxRetries)
    : maxRetries(maxRetries), retryDelay(std::chrono::seconds(5)) {}

void RetryQueue::addToQueue(const Transaction& transaction, std::function<bool(const Transaction&)> retryFunc) {
    RetryItem item;
    item.transaction = transaction;
    item.attemptCount = 0;
    item.nextRetryTime = std::chrono::system_clock::now() + retryDelay;
    item.retryFunction = retryFunc;
    
    queue.push(item);
    std::cout << "[RetryQueue] Added transaction to retry queue" << std::endl;
}

void RetryQueue::processQueue() {
    auto now = std::chrono::system_clock::now();
    std::queue<RetryItem> remainingItems;
    
    while (!queue.empty()) {
        RetryItem item = queue.front();
        queue.pop();
        
        // Check if it's time to retry
        if (now < item.nextRetryTime) {
            remainingItems.push(item);
            continue;
        }
        
        // Attempt retry
        item.attemptCount++;
        std::cout << "[RetryQueue] Retrying transaction (attempt " << item.attemptCount << ")" << std::endl;
        
        bool success = item.retryFunction(item.transaction);
        
        if (!success && item.attemptCount < maxRetries) {
            // Retry failed, add back to queue with exponential backoff
            item.nextRetryTime = now + retryDelay * item.attemptCount;
            remainingItems.push(item);
        } else if (!success) {
            std::cout << "[RetryQueue] Transaction failed after " << maxRetries << " attempts" << std::endl;
        } else {
            std::cout << "[RetryQueue] Transaction succeeded on retry" << std::endl;
        }
    }
    
    queue = remainingItems;
}

int RetryQueue::getPendingCount() const {
    return queue.size();
}

void RetryQueue::clearQueue() {
    while (!queue.empty()) {
        queue.pop();
    }
}

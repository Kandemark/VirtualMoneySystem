#ifndef RETRY_QUEUE_H
#define RETRY_QUEUE_H

#include "../transactions/Transaction.h"
#include <queue>
#include <chrono>
#include <functional>

struct RetryItem {
    Transaction transaction;
    int attemptCount;
    std::chrono::system_clock::time_point nextRetryTime;
    std::function<bool(const Transaction&)> retryFunction;
};

class RetryQueue {
public:
    RetryQueue(int maxRetries = 3);

    void addToQueue(const Transaction& transaction, std::function<bool(const Transaction&)> retryFunc);
    void processQueue();
    int getPendingCount() const;
    void clearQueue();

private:
    std::queue<RetryItem> queue;
    int maxRetries;
    std::chrono::seconds retryDelay;
};

#endif // RETRY_QUEUE_H

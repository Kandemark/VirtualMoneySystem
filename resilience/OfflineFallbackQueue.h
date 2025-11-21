/**
 * @file OfflineFallbackQueue.h
 * @brief Offline fallback queue
 */

#ifndef OFFLINE_FALLBACK_QUEUE_H
#define OFFLINE_FALLBACK_QUEUE_H

#include <string>
#include <vector>

class OfflineFallbackQueue {
public:
    void enqueue(const std::string& operation);
    std::vector<std::string> dequeueAll();
    int getQueueSize();
};

#endif

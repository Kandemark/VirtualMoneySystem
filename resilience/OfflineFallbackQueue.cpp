/**
 * @file OfflineFallbackQueue.cpp
 */

#include "OfflineFallbackQueue.h"
#include <iostream>

OfflineFallbackQueue::OfflineFallbackQueue() {}

void OfflineFallbackQueue::enqueue(const std::string& operation) {
    queue.push_back(operation);
    std::cout << "Operation queued for offline processing: " << operation << std::endl;
}

std::vector<std::string> OfflineFallbackQueue::dequeueAll() {
    std::vector<std::string> operations = queue;
    queue.clear();
    std::cout << "Dequeued " << operations.size() << " operations" << std::endl;
    return operations;
}

int OfflineFallbackQueue::size() const {
    return queue.size();
}

bool OfflineFallbackQueue::isEmpty() const {
    return queue.empty();
}

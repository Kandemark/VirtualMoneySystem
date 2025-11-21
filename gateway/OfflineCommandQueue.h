/**
 * @file OfflineCommandQueue.h
 * @brief Offline command queuing
 */

#ifndef OFFLINE_COMMAND_QUEUE_H
#define OFFLINE_COMMAND_QUEUE_H

#include <string>
#include <vector>

class OfflineCommandQueue {
public:
    void queueCommand(const std::string& command, const std::string& userId);
    void processQueue();
    std::vector<std::string> getPendingCommands();
    void clearQueue();
};

#endif

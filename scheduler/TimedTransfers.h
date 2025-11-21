/**
 * @file TimedTransfers.h
 * @brief Timed transfer scheduling
 */

#ifndef TIMED_TRANSFERS_H
#define TIMED_TRANSFERS_H

#include <string>

class TimedTransfers {
public:
    void scheduleTransfer(const std::string& fromUserId, const std::string& toUserId, double amount, const std::string& time);
    void executeScheduledTransfers();
};

#endif

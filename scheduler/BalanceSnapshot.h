/**
 * @file BalanceSnapshot.h
 * @brief Scheduled balance snapshots
 */

#ifndef BALANCE_SNAPSHOT_H
#define BALANCE_SNAPSHOT_H

#include <string>

class BalanceSnapshot {
public:
    void takeSnapshot(const std::string& userId);
    std::string getSnapshot(const std::string& userId, const std::string& date);
};

#endif

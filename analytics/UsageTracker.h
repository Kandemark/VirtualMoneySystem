#ifndef USAGE_TRACKER_H
#define USAGE_TRACKER_H

#include "../core/TransactionEngine.h"
#include <string>
#include <map>

class UsageTracker {
public:
    UsageTracker(const TransactionEngine& transactionEngine);

    int getTransactionCount(const std::string& userId) const;
    double getTotalVolumeByUser(const std::string& userId) const;
    std::map<std::string, int> getUserActivityMap() const;

private:
    const TransactionEngine& transactionEngine;
};

#endif // USAGE_TRACKER_H

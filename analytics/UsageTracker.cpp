#include "UsageTracker.h"

UsageTracker::UsageTracker(const TransactionEngine& transactionEngine)
    : transactionEngine(transactionEngine) {}

int UsageTracker::getTransactionCount(const std::string& userId) const {
    const auto& history = transactionEngine.getTransactionHistory();
    int count = 0;

    for (const auto& transaction : history) {
        if (transaction.getSenderId() == userId || transaction.getReceiverId() == userId) {
            count++;
        }
    }

    return count;
}

double UsageTracker::getTotalVolumeByUser(const std::string& userId) const {
    const auto& history = transactionEngine.getTransactionHistory();
    double volume = 0.0;

    for (const auto& transaction : history) {
        if (transaction.getSenderId() == userId) {
            volume += transaction.getAmount();
        }
    }

    return volume;
}

std::map<std::string, int> UsageTracker::getUserActivityMap() const {
    const auto& history = transactionEngine.getTransactionHistory();
    std::map<std::string, int> activityMap;

    for (const auto& transaction : history) {
        activityMap[transaction.getSenderId()]++;
        activityMap[transaction.getReceiverId()]++;
    }

    return activityMap;
}

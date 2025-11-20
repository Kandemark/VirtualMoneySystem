#include "DashboardData.h"
#include <set>
#include <chrono>

DashboardData::DashboardData(const TransactionEngine& transactionEngine, DatabaseManager& dbManager)
    : transactionEngine(transactionEngine), dbManager(dbManager) {}

DashboardMetrics DashboardData::getMetrics() const {
    DashboardMetrics metrics;
    const auto& history = transactionEngine.getTransactionHistory();

    // Total transactions
    metrics.totalTransactions = history.size();

    // Total volume and volume by currency
    metrics.totalVolume = 0.0;
    for (const auto& transaction : history) {
        metrics.totalVolume += transaction.getAmount();
        metrics.volumeByCurrency[transaction.getCurrency()] += transaction.getAmount();
    }

    // Active users today
    std::set<std::string> activeToday;
    auto now = std::chrono::system_clock::now();
    auto dayAgo = now - std::chrono::hours(24);

    for (const auto& transaction : history) {
        if (transaction.getTimestamp() >= dayAgo) {
            activeToday.insert(transaction.getSenderId());
            activeToday.insert(transaction.getReceiverId());
        }
    }
    metrics.activeUsersToday = activeToday.size();

    // Total users (placeholder - would need to query database)
    metrics.totalUsers = 0;

    return metrics;
}

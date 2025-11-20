#include "UsageAnalytics.h"
#include <set>
#include <chrono>

UsageAnalytics::UsageAnalytics(const TransactionEngine& transactionEngine)
    : transactionEngine(transactionEngine) {}

int UsageAnalytics::getDailyActiveUsers() const {
    const auto& history = transactionEngine.getTransactionHistory();
    std::set<std::string> activeUsers;

    auto now = std::chrono::system_clock::now();
    auto dayAgo = now - std::chrono::hours(24);

    for (const auto& transaction : history) {
        if (transaction.getTimestamp() >= dayAgo) {
            activeUsers.insert(transaction.getSenderId());
            activeUsers.insert(transaction.getReceiverId());
        }
    }

    return activeUsers.size();
}

int UsageAnalytics::getMonthlyActiveUsers() const {
    const auto& history = transactionEngine.getTransactionHistory();
    std::set<std::string> activeUsers;

    auto now = std::chrono::system_clock::now();
    auto monthAgo = now - std::chrono::hours(24 * 30);

    for (const auto& transaction : history) {
        if (transaction.getTimestamp() >= monthAgo) {
            activeUsers.insert(transaction.getSenderId());
            activeUsers.insert(transaction.getReceiverId());
        }
    }

    return activeUsers.size();
}

double UsageAnalytics::getAverageTransactionValue() const {
    const auto& history = transactionEngine.getTransactionHistory();
    
    if (history.empty()) {
        return 0.0;
    }

    double total = 0.0;
    for (const auto& transaction : history) {
        total += transaction.getAmount();
    }

    return total / history.size();
}

#include "BusinessInsights.h"

BusinessInsights::BusinessInsights(const TransactionEngine& transactionEngine)
    : transactionEngine(transactionEngine) {}

double BusinessInsights::getTotalRevenue() const {
    const auto& history = transactionEngine.getTransactionHistory();
    double revenue = 0.0;

    for (const auto& transaction : history) {
        revenue += transaction.getAmount();
    }

    return revenue;
}

double BusinessInsights::getGrowthRate() const {
    const auto& history = transactionEngine.getTransactionHistory();
    if (history.size() < 2) {
        return 0.0;
    }
    
    // Calculate month-over-month growth based on transaction volume
    time_t now = time(0);
    time_t oneMonthAgo = now - (30 * 24 * 60 * 60);
    
    double currentMonthTotal = 0.0;
    double previousMonthTotal = 0.0;
    time_t twoMonthsAgo = now - (60 * 24 * 60 * 60);
    
    for (const auto& transaction : history) {
        if (transaction.getTimestamp() >= oneMonthAgo) {
            currentMonthTotal += transaction.getAmount();
        } else if (transaction.getTimestamp() >= twoMonthsAgo) {
            previousMonthTotal += transaction.getAmount();
        }
    }
    
    if (previousMonthTotal == 0.0) {
        return currentMonthTotal > 0 ? 100.0 : 0.0;
    }
    
    return ((currentMonthTotal - previousMonthTotal) / previousMonthTotal) * 100.0;
}

int BusinessInsights::getCustomerRetentionRate() const {
    // For this implementation, we'll calculate retention based on
    // recurring transaction patterns in the last 60 days
    const auto& history = transactionEngine.getTransactionHistory();
    
    time_t now = time(0);
    time_t thirtyDaysAgo = now - (30 * 24 * 60 * 60);
    time_t sixtyDaysAgo = now - (60 * 24 * 60 * 60);
    
    std::set<std::string> usersLast30Days;
    std::set<std::string> usersPrevious30Days;
    
    for (const auto& transaction : history) {
        if (transaction.getTimestamp() >= thirtyDaysAgo) {
            usersLast30Days.insert(transaction.getFromUserId());
            usersLast30Days.insert(transaction.getToUserId());
        } else if (transaction.getTimestamp() >= sixtyDaysAgo) {
            usersPrevious30Days.insert(transaction.getFromUserId());
            usersPrevious30Days.insert(transaction.getToUserId());
        }
    }
    
    if (usersPrevious30Days.empty()) {
        return usersLast30Days.empty() ? 100 : 85; // Default retention
    }
    
    int retainedUsers = 0;
    for (const auto& user : usersPrevious30Days) {
        if (usersLast30Days.find(user) != usersLast30Days.end()) {
            retainedUsers++;
        }
    }
    
    return (retainedUsers * 100) / usersPrevious30Days.size();
}

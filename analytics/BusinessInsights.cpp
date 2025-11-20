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
    // Calculate month-over-month growth
    // Placeholder: return 10% growth
    return 10.0;
}

int BusinessInsights::getCustomerRetentionRate() const {
    // Calculate customer retention percentage
    // Placeholder: return 85% retention
    return 85;
}

#include "AccountInsights.h"
#include <map>

AccountInsights::AccountInsights(const TransactionEngine& transactionEngine)
    : transactionEngine(transactionEngine) {}

double AccountInsights::getAverageTransactionSize(const std::string& userId) const {
    const auto& history = transactionEngine.getTransactionHistory();
    double total = 0.0;
    int count = 0;

    for (const auto& transaction : history) {
        if (transaction.getSenderId() == userId) {
            total += transaction.getAmount();
            count++;
        }
    }

    return count > 0 ? total / count : 0.0;
}

int AccountInsights::getMostActiveHour(const std::string& userId) const {
    // Analyze transaction timestamps to find most active hour
    // Placeholder: return 12 (noon) as default
    return 12;
}

std::string AccountInsights::getPreferredCurrency(const std::string& userId) const {
    const auto& history = transactionEngine.getTransactionHistory();
    std::map<std::string, int> currencyCount;

    for (const auto& transaction : history) {
        if (transaction.getSenderId() == userId) {
            currencyCount[transaction.getCurrency()]++;
        }
    }

    std::string preferredCurrency = "USD";
    int maxCount = 0;

    for (const auto& [currency, count] : currencyCount) {
        if (count > maxCount) {
            maxCount = count;
            preferredCurrency = currency;
        }
    }

    return preferredCurrency;
}

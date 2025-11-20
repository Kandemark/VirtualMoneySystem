#ifndef USAGE_ANALYTICS_H
#define USAGE_ANALYTICS_H

#include "../core/TransactionEngine.h"
#include <string>

class UsageAnalytics {
public:
    UsageAnalytics(const TransactionEngine& transactionEngine);

    int getDailyActiveUsers() const;
    int getMonthlyActiveUsers() const;
    double getAverageTransactionValue() const;

private:
    const TransactionEngine& transactionEngine;
};

#endif // USAGE_ANALYTICS_H

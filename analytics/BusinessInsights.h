#ifndef BUSINESS_INSIGHTS_H
#define BUSINESS_INSIGHTS_H

#include "../core/TransactionEngine.h"
#include <string>
#include <set>
#include <ctime>

class BusinessInsights {
public:
    BusinessInsights(const TransactionEngine& transactionEngine);

    double getTotalRevenue() const;
    double getGrowthRate() const;
    int getCustomerRetentionRate() const;

private:
    const TransactionEngine& transactionEngine;
};

#endif // BUSINESS_INSIGHTS_H

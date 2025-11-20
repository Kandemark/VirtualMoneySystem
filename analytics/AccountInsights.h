#ifndef ACCOUNT_INSIGHTS_H
#define ACCOUNT_INSIGHTS_H

#include "../core/TransactionEngine.h"
#include <string>

class AccountInsights {
public:
    AccountInsights(const TransactionEngine& transactionEngine);

    double getAverageTransactionSize(const std::string& userId) const;
    int getMostActiveHour(const std::string& userId) const;
    std::string getPreferredCurrency(const std::string& userId) const;

private:
    const TransactionEngine& transactionEngine;
};

#endif // ACCOUNT_INSIGHTS_H

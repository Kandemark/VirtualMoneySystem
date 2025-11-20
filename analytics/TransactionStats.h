#ifndef TRANSACTION_STATS_H
#define TRANSACTION_STATS_H

#include "../core/TransactionEngine.h"
#include <map>
#include <string>

class TransactionStats {
public:
    TransactionStats(const TransactionEngine& transactionEngine);

    // Returns total volume per currency
    std::map<std::string, double> getTotalVolume() const;

    // Returns total number of transactions
    int getTotalCount() const;

private:
    const TransactionEngine& transactionEngine;
};

#endif // TRANSACTION_STATS_H

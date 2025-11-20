#ifndef TREND_GRAPHS_H
#define TREND_GRAPHS_H

#include "../core/TransactionEngine.h"
#include <vector>
#include <string>

struct TrendDataPoint {
    std::string date;
    double value;
};

class TrendGraphs {
public:
    TrendGraphs(const TransactionEngine& transactionEngine);

    std::vector<TrendDataPoint> getVolumeOverTime() const;
    std::vector<TrendDataPoint> getTransactionCountOverTime() const;

private:
    const TransactionEngine& transactionEngine;
};

#endif // TREND_GRAPHS_H

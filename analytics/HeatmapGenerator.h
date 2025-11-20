#ifndef HEATMAP_GENERATOR_H
#define HEATMAP_GENERATOR_H

#include "../core/TransactionEngine.h"
#include <string>
#include <vector>

struct HeatmapCell {
    int hour;
    int dayOfWeek;
    int transactionCount;
};

class HeatmapGenerator {
public:
    HeatmapGenerator(const TransactionEngine& transactionEngine);

    std::vector<HeatmapCell> generateTransactionHeatmap() const;

private:
    const TransactionEngine& transactionEngine;
};

#endif // HEATMAP_GENERATOR_H

#ifndef SEGMENTED_STATS_H
#define SEGMENTED_STATS_H

#include "../core/TransactionEngine.h"
#include <string>
#include <map>

class SegmentedStats {
public:
    SegmentedStats(const TransactionEngine& transactionEngine);

    std::map<std::string, double> getVolumeBySegment(const std::string& segmentType) const;
    std::map<std::string, int> getCountBySegment(const std::string& segmentType) const;

private:
    const TransactionEngine& transactionEngine;
};

#endif // SEGMENTED_STATS_H

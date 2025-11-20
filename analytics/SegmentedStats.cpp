#include "SegmentedStats.h"

SegmentedStats::SegmentedStats(const TransactionEngine& transactionEngine)
    : transactionEngine(transactionEngine) {}

std::map<std::string, double> SegmentedStats::getVolumeBySegment(const std::string& segmentType) const {
    const auto& history = transactionEngine.getTransactionHistory();
    std::map<std::string, double> volumeBySegment;

    if (segmentType == "currency") {
        for (const auto& transaction : history) {
            volumeBySegment[transaction.getCurrency()] += transaction.getAmount();
        }
    }

    return volumeBySegment;
}

std::map<std::string, int> SegmentedStats::getCountBySegment(const std::string& segmentType) const {
    const auto& history = transactionEngine.getTransactionHistory();
    std::map<std::string, int> countBySegment;

    if (segmentType == "currency") {
        for (const auto& transaction : history) {
            countBySegment[transaction.getCurrency()]++;
        }
    }

    return countBySegment;
}

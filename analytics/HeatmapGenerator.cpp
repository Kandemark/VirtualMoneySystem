#include "HeatmapGenerator.h"
#include <chrono>
#include <map>

HeatmapGenerator::HeatmapGenerator(const TransactionEngine& transactionEngine)
    : transactionEngine(transactionEngine) {}

std::vector<HeatmapCell> HeatmapGenerator::generateTransactionHeatmap() const {
    const auto& history = transactionEngine.getTransactionHistory();
    std::map<std::pair<int, int>, int> heatmapData;

    for (const auto& transaction : history) {
        auto timestamp = transaction.getTimestamp();
        auto time = std::chrono::system_clock::to_time_t(timestamp);
        auto tm = *std::localtime(&time);
        
        int hour = tm.tm_hour;
        int dayOfWeek = tm.tm_wday;
        
        heatmapData[{hour, dayOfWeek}]++;
    }

    std::vector<HeatmapCell> heatmap;
    for (const auto& [key, count] : heatmapData) {
        heatmap.push_back({key.first, key.second, count});
    }

    return heatmap;
}

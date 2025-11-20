#include "TrendGraphs.h"
#include <map>
#include <chrono>
#include <iomanip>
#include <sstream>

TrendGraphs::TrendGraphs(const TransactionEngine& transactionEngine)
    : transactionEngine(transactionEngine) {}

std::vector<TrendDataPoint> TrendGraphs::getVolumeOverTime() const {
    const auto& history = transactionEngine.getTransactionHistory();
    std::map<std::string, double> volumeByDate;

    for (const auto& transaction : history) {
        auto timestamp = transaction.getTimestamp();
        auto time = std::chrono::system_clock::to_time_t(timestamp);
        auto tm = *std::localtime(&time);
        
        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y-%m-%d");
        std::string date = oss.str();
        
        volumeByDate[date] += transaction.getAmount();
    }

    std::vector<TrendDataPoint> trend;
    for (const auto& [date, volume] : volumeByDate) {
        trend.push_back({date, volume});
    }

    return trend;
}

std::vector<TrendDataPoint> TrendGraphs::getTransactionCountOverTime() const {
    const auto& history = transactionEngine.getTransactionHistory();
    std::map<std::string, int> countByDate;

    for (const auto& transaction : history) {
        auto timestamp = transaction.getTimestamp();
        auto time = std::chrono::system_clock::to_time_t(timestamp);
        auto tm = *std::localtime(&time);
        
        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y-%m-%d");
        std::string date = oss.str();
        
        countByDate[date]++;
    }

    std::vector<TrendDataPoint> trend;
    for (const auto& [date, count] : countByDate) {
        trend.push_back({date, static_cast<double>(count)});
    }

    return trend;
}

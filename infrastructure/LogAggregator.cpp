#include "LogAggregator.h"

void LogAggregator::log(const std::string& level, const std::string& message, const std::string& source) {
    LogEntry entry;
    entry.timestamp = "2024-01-01 12:00:00";
    entry.level = level;
    entry.message = message;
    entry.source = source;
    logs.push_back(entry);
}

std::vector<LogEntry> LogAggregator::getLogs(const std::string& level) {
    if (level.empty()) {
        return logs;
    }
    
    std::vector<LogEntry> filtered;
    for (const auto& entry : logs) {
        if (entry.level == level) {
            filtered.push_back(entry);
        }
    }
    return filtered;
}

void LogAggregator::clearLogs() {
    logs.clear();
}

/**
 * @file LogAggregator.h
 * @brief Centralized log aggregation
 */

#ifndef LOG_AGGREGATOR_H
#define LOG_AGGREGATOR_H

#include <string>
#include <vector>

struct LogEntry {
    std::string timestamp;
    std::string level;
    std::string message;
    std::string source;
};

class LogAggregator {
public:
    void log(const std::string& level, const std::string& message, const std::string& source);
    std::vector<LogEntry> getLogs(const std::string& level = "");
    void clearLogs();
private:
    std::vector<LogEntry> logs;
};

#endif

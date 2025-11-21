/**
 * @file HistoryQueryEngine.h
 * @brief Query historical data
 */

#ifndef HISTORY_QUERY_ENGINE_H
#define HISTORY_QUERY_ENGINE_H

#include <string>
#include <vector>
#include <map>

class HistoryQueryEngine {
public:
    std::vector<std::map<std::string, std::string>> query(const std::string& queryString);
    std::vector<std::map<std::string, std::string>> filterByDateRange(const std::string& startDate, const std::string& endDate);
    std::vector<std::map<std::string, std::string>> filterByUser(const std::string& userId);
};

#endif

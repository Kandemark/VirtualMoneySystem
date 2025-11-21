/**
 * @file SearchEngine.h
 * @brief Search historical records
 */

#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include <string>
#include <vector>

class SearchEngine {
public:
    std::vector<std::string> search(const std::string& query);
    std::vector<std::string> searchTransactions(const std::string& query);
    std::vector<std::string> searchUsers(const std::string& query);
    void indexData(const std::string& dataType, const std::string& data);
};

#endif

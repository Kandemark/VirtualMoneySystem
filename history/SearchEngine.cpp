#include "SearchEngine.h"

#include <unordered_map>

namespace { std::unordered_multimap<std::string, std::string> g_index; }

std::vector<std::string> SearchEngine::search(const std::string& query) {
    std::vector<std::string> out;
    for (const auto& [type, value] : g_index) if (value.find(query) != std::string::npos) out.push_back(type + ":" + value);
    return out;
}

std::vector<std::string> SearchEngine::searchTransactions(const std::string& query) {
    std::vector<std::string> out;
    for (const auto& [type, value] : g_index) if (type == "transaction" && value.find(query) != std::string::npos) out.push_back(value);
    return out;
}

std::vector<std::string> SearchEngine::searchUsers(const std::string& query) {
    std::vector<std::string> out;
    for (const auto& [type, value] : g_index) if (type == "user" && value.find(query) != std::string::npos) out.push_back(value);
    return out;
}

void SearchEngine::indexData(const std::string& dataType, const std::string& data) { g_index.emplace(dataType, data); }

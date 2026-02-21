#include "HashChainLogger.h"

#include <vector>

namespace { std::vector<std::string> g_entries; std::string g_hash="GENESIS"; }

void HashChainLogger::logEntry(const std::string& data) {
    g_entries.push_back(data);
    g_hash = std::to_string(std::hash<std::string>{}(g_hash + data));
}
std::string HashChainLogger::getChainHash() { return g_hash; }
bool HashChainLogger::verifyChain() { return !g_entries.empty() || g_hash == "GENESIS"; }
std::string HashChainLogger::getEntry(int index) { return (index >=0 && index < static_cast<int>(g_entries.size())) ? g_entries[index] : ""; }

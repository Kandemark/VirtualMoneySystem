#include "TransactionHistory.h"

#include <fstream>
#include <vector>

namespace { std::vector<std::string> g_log; }

void TransactionHistoryLogs::logTransaction(const std::string& transactionId) { g_log.push_back(transactionId); }
void TransactionHistoryLogs::writeToLog(const std::string& filename) {
    std::ofstream out(filename, std::ios::app);
    for (const auto& id : g_log) out << id << '
';
}

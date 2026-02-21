#include "TransactionHistory.h"

#include <algorithm>

namespace {
std::vector<HistoricalTransaction> g_transactions;
}

std::vector<HistoricalTransaction> TransactionHistory::getHistory(const std::string& userId, int) {
    std::vector<HistoricalTransaction> out;
    for (const auto& tx : g_transactions) if (tx.userId == userId) out.push_back(tx);
    return out;
}

void TransactionHistory::recordTransaction(const HistoricalTransaction& transaction) { g_transactions.push_back(transaction); }

std::vector<HistoricalTransaction> TransactionHistory::searchTransactions(const std::string& query) {
    std::vector<HistoricalTransaction> out;
    for (const auto& tx : g_transactions) {
        if (tx.transactionId.find(query) != std::string::npos || tx.type.find(query) != std::string::npos) out.push_back(tx);
    }
    return out;
}

void TransactionHistory::archiveOldTransactions(int daysToKeep) {
    if (daysToKeep <= 0) g_transactions.clear();
}

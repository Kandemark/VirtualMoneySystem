/**
 * @file TransactionHistory.h
 * @brief Transaction history management
 */

#ifndef TRANSACTION_HISTORY_H
#define TRANSACTION_HISTORY_H

#include <string>
#include <vector>

struct HistoricalTransaction {
    std::string transactionId;
    std::string userId;
    double amount;
    std::string type;
    std::string timestamp;
};

class TransactionHistory {
public:
    std::vector<HistoricalTransaction> getHistory(const std::string& userId, int days = 30);
    void recordTransaction(const HistoricalTransaction& transaction);
    std::vector<HistoricalTransaction> searchTransactions(const std::string& query);
    void archiveOldTransactions(int daysToKeep);
};

#endif

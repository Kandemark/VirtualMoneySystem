/**
 * @file TransactionHistory.h
 * @brief Transaction history for logs directory
 */

#ifndef TRANSACTION_HISTORY_LOGS_H
#define TRANSACTION_HISTORY_LOGS_H

#include <string>

class TransactionHistoryLogs {
public:
    void logTransaction(const std::string& transactionId);
    void writeToLog(const std::string& filename);
};

#endif

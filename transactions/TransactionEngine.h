/**
 * @file TransactionEngine.h
 * @brief Core transaction processing engine
 */

#ifndef TRANSACTION_ENGINE_H
#define TRANSACTION_ENGINE_H

#include <string>

class TransactionEngine {
public:
    std::string createTransaction(const std::string& fromWallet, const std::string& toWallet, double amount, const std::string& currency = "USD");
    bool validateTransaction(const std::string& transactionId);
    std::string getTransactionStatus(const std::string& transactionId);
    void rollbackTransaction(const std::string& transactionId);
};

#endif

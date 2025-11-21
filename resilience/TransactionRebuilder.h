/**
 * @file TransactionRebuilder.h
 * @brief Transaction rebuilding for recovery
 */

#ifndef TRANSACTION_REBUILDER_H
#define TRANSACTION_REBUILDER_H

#include <string>

class TransactionRebuilder {
public:
    void rebuildTransaction(const std::string& transactionId);
    bool verifyRebuild(const std::string& transactionId);
};

#endif

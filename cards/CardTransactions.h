/**
 * @file CardTransactions.h
 * @brief Card transaction processing
 */

#ifndef CARD_TRANSACTIONS_H
#define CARD_TRANSACTIONS_H

#include <string>
#include <vector>

struct CardTransaction {
    std::string transactionId;
    std::string cardId;
    double amount;
    std::string merchant;
    std::string timestamp;
};

class CardTransactions {
public:
    bool authorizeTransaction(const std::string& cardId, double amount);
    void recordTransaction(const std::string& cardId, double amount, const std::string& merchant);
    std::vector<CardTransaction> getTransactionHistory(const std::string& cardId);
private:
    std::vector<CardTransaction> transactions;
};

#endif

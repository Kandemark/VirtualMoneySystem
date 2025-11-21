#include "CardTransactions.h"
#include <iostream>

bool CardTransactions::authorizeTransaction(const std::string& cardId, double amount) {
    std::cout << "[Card] Authorizing $" << amount << " for card " << cardId << std::endl;
    return true;
}

void CardTransactions::recordTransaction(const std::string& cardId, double amount, const std::string& merchant) {
    CardTransaction txn;
    txn.transactionId = "TXN_" + std::to_string(transactions.size() + 1);
    txn.cardId = cardId;
    txn.amount = amount;
    txn.merchant = merchant;
    txn.timestamp = "2024-01-01 12:00:00";
    transactions.push_back(txn);
}

std::vector<CardTransaction> CardTransactions::getTransactionHistory(const std::string& cardId) {
    std::vector<CardTransaction> history;
    for (const auto& txn : transactions) {
        if (txn.cardId == cardId) {
            history.push_back(txn);
        }
    }
    return history;
}

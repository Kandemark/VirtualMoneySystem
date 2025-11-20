#include "LedgerManager.h"

LedgerManager::LedgerManager() {}

void LedgerManager::recordTransaction(const Transaction& transaction) {
    ledger.push_back(transaction);
}

std::vector<Transaction> LedgerManager::getTransactionsByUser(const std::string& userId) const {
    std::vector<Transaction> userTransactions;
    
    for (const auto& transaction : ledger) {
        if (transaction.getSenderId() == userId || transaction.getReceiverId() == userId) {
            userTransactions.push_back(transaction);
        }
    }
    
    return userTransactions;
}

std::vector<Transaction> LedgerManager::getAllTransactions() const {
    return ledger;
}

double LedgerManager::calculateBalance(const std::string& userId, const std::string& currency) const {
    double balance = 0.0;
    
    for (const auto& transaction : ledger) {
        if (transaction.getCurrency() != currency) {
            continue;
        }
        
        if (transaction.getSenderId() == userId) {
            balance -= transaction.getAmount();
        }
        
        if (transaction.getReceiverId() == userId) {
            balance += transaction.getAmount();
        }
    }
    
    return balance;
}

int LedgerManager::getTransactionCount() const {
    return ledger.size();
}

/**
 * @file TransactionEngine.cpp
 */

#include "TransactionEngine.h"
#include <iostream>

namespace VirtualMoney {

TransactionEngine::TransactionEngine() {}

std::string TransactionEngine::createTransaction(const std::string& from, const std::string& to, double amount) {
    Transaction tx;
    tx.id = "TX_" + std::to_string(transactions.size() + 1);
    tx.from = from;
    tx.to = to;
    tx.amount = amount;
    tx.status = "pending";
    tx.timestamp = std::time(nullptr);
    
    transactions[tx.id] = tx;
    
    std::cout << "Transaction created: " << tx.id << std::endl;
    
    return tx.id;
}

bool TransactionEngine::executeTransaction(const std::string& txId) {
    auto it = transactions.find(txId);
    if (it != transactions.end()) {
        it->second.status = "completed";
        std::cout << "Transaction executed: " << txId << std::endl;
        return true;
    }
    return false;
}

std::string TransactionEngine::getTransactionStatus(const std::string& txId) {
    auto it = transactions.find(txId);
    if (it != transactions.end()) {
        return it->second.status;
    }
    return "not_found";
}

} // namespace VirtualMoney

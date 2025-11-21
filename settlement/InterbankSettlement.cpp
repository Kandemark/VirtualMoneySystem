/**
 * @file InterbankSettlement.cpp
 */

#include "InterbankSettlement.h"
#include <random>
#include <sstream>
#include <iostream>
#include <algorithm>

namespace VirtualMoney {

InterbankSettlement::InterbankSettlement() {}

std::string InterbankSettlement::submitTransaction(const InterbankTransaction& tx) {
    if (!validateTransaction(tx)) {
        return "";
    }
    
    InterbankTransaction newTx = tx;
    newTx.txId = generateTxId();
    newTx.timestamp = std::time(nullptr);
    newTx.settled = false;
    
    transactions[newTx.txId] = newTx;
    
    std::cout << "Interbank transaction submitted: " << newTx.txId 
              << " (" << newTx.sendingBank << " -> " << newTx.receivingBank 
              << ", $" << newTx.amount << ")" << std::endl;
    
    // Auto-settle RTGS transactions
    if (newTx.settlementMethod == "RTGS") {
        settleRTGS(newTx.txId);
    }
    
    return newTx.txId;
}

bool InterbankSettlement::settleRTGS(const std::string& txId) {
    auto it = transactions.find(txId);
    if (it == transactions.end()) {
        return false;
    }
    
    // Real-Time Gross Settlement
    it->second.settled = true;
    
    std::cout << "RTGS settlement completed: " << txId 
              << " (instant settlement)" << std::endl;
    
    return true;
}

std::string InterbankSettlement::createSettlementBatch(const std::vector<std::string>& txIds) {
    SettlementBatch batch;
    batch.batchId = generateBatchId();
    batch.cutoffTime = std::time(nullptr);
    batch.processed = false;
    batch.netAmount = 0.0;
    
    for (const auto& txId : txIds) {
        auto it = transactions.find(txId);
        if (it != transactions.end() && !it->second.settled) {
            batch.transactions.push_back(it->second);
            batch.netAmount += it->second.amount;
        }
    }
    
    batches[batch.batchId] = batch;
    
    std::cout << "Settlement batch created: " << batch.batchId 
              << " (" << batch.transactions.size() << " transactions, "
              << "net: $" << batch.netAmount << ")" << std::endl;
    
    return batch.batchId;
}

bool InterbankSettlement::processSettlementBatch(const std::string& batchId) {
    auto it = batches.find(batchId);
    if (it == batches.end()) {
        return false;
    }
    
    // Process all transactions in batch
    for (auto& tx : it->second.transactions) {
        auto txIt = transactions.find(tx.txId);
        if (txIt != transactions.end()) {
            txIt->second.settled = true;
        }
    }
    
    it->second.processed = true;
    
    std::cout << "Settlement batch processed: " << batchId 
              << " (" << it->second.transactions.size() << " transactions settled)" 
              << std::endl;
    
    return true;
}

double InterbankSettlement::calculateNetPosition(const std::string& bankId) {
    double netPosition = 0.0;
    
    for (const auto& [id, tx] : transactions) {
        if (tx.sendingBank == bankId) {
            netPosition -= tx.amount;
        }
        if (tx.receivingBank == bankId) {
            netPosition += tx.amount;
        }
    }
    
    std::cout << "Net position for " << bankId << ": $" << netPosition << std::endl;
    
    return netPosition;
}

std::vector<InterbankTransaction> InterbankSettlement::getPendingTransactions(const std::string& bankId) {
    std::vector<InterbankTransaction> pending;
    
    for (const auto& [id, tx] : transactions) {
        if (!tx.settled && (tx.sendingBank == bankId || tx.receivingBank == bankId)) {
            pending.push_back(tx);
        }
    }
    
    return pending;
}

InterbankSettlement::SettlementStats InterbankSettlement::getStatistics() const {
    SettlementStats stats;
    stats.totalTransactions = transactions.size();
    stats.totalVolume = 0.0;
    stats.averageSettlementTime = 0.0;
    stats.pendingCount = 0;
    
    for (const auto& [id, tx] : transactions) {
        stats.totalVolume += tx.amount;
        if (!tx.settled) {
            stats.pendingCount++;
        }
    }
    
    // Average settlement time (simplified)
    stats.averageSettlementTime = 2.5; // 2.5 seconds average
    
    return stats;
}

std::string InterbankSettlement::generateTxId() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(100000000, 999999999);
    
    std::stringstream ss;
    ss << "IB_" << dis(gen);
    return ss.str();
}

std::string InterbankSettlement::generateBatchId() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(100000, 999999);
    
    std::stringstream ss;
    ss << "BATCH_" << dis(gen);
    return ss.str();
}

bool InterbankSettlement::validateTransaction(const InterbankTransaction& tx) {
    if (tx.amount <= 0) return false;
    if (tx.sendingBank.empty() || tx.receivingBank.empty()) return false;
    if (tx.sendingBank == tx.receivingBank) return false;
    return true;
}

} // namespace VirtualMoney

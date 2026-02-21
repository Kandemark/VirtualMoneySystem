#include "TransactionPool.h"
#include <algorithm>
#include <chrono>

TransactionPool::TransactionPool(size_t maxSize) : maxPoolSize(maxSize) {}

bool TransactionPool::addTransaction(const std::string &txId,
                                     const std::string &from,
                                     const std::string &to, double amount,
                                     const std::string &currency) {
  std::lock_guard<std::mutex> lock(poolMutex);

  if (pendingTransactions.size() >= maxPoolSize) {
    return false; // Pool is full
  }

  Transaction tx;
  tx.id = txId;
  tx.from = from;
  tx.to = to;
  tx.amount = amount;
  tx.currency = currency;
  tx.timestamp = std::chrono::system_clock::now();
  tx.status = "pending";

  pendingTransactions.push_back(tx);
  return true;
}

std::vector<TransactionPool::Transaction>
TransactionPool::getPendingTransactions(size_t count) {
  std::lock_guard<std::mutex> lock(poolMutex);

  size_t numToReturn = std::min(count, pendingTransactions.size());
  std::vector<Transaction> result(pendingTransactions.begin(),
                                  pendingTransactions.begin() + numToReturn);
  return result;
}

bool TransactionPool::removeTransaction(const std::string &txId) {
  std::lock_guard<std::mutex> lock(poolMutex);

  auto it =
      std::find_if(pendingTransactions.begin(), pendingTransactions.end(),
                   [&txId](const Transaction &tx) { return tx.id == txId; });

  if (it != pendingTransactions.end()) {
    pendingTransactions.erase(it);
    return true;
  }
  return false;
}

size_t TransactionPool::getSize() const {
  std::lock_guard<std::mutex> lock(poolMutex);
  return pendingTransactions.size();
}

void TransactionPool::clear() {
  std::lock_guard<std::mutex> lock(poolMutex);
  pendingTransactions.clear();
}

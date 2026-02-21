#pragma once
#include <chrono>
#include <mutex>
#include <string>
#include <vector>


class TransactionPool {
public:
  struct Transaction {
    std::string id;
    std::string from;
    std::string to;
    double amount;
    std::string currency;
    std::chrono::system_clock::time_point timestamp;
    std::string status;
  };

  explicit TransactionPool(size_t maxSize = 10000);

  bool addTransaction(const std::string &txId, const std::string &from,
                      const std::string &to, double amount,
                      const std::string &currency);

  std::vector<Transaction> getPendingTransactions(size_t count);
  bool removeTransaction(const std::string &txId);
  size_t getSize() const;
  void clear();

private:
  size_t maxPoolSize;
  std::vector<Transaction> pendingTransactions;
  mutable std::mutex poolMutex;
};

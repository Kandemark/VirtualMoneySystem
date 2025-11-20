#ifndef TRANSACTION_THROTTLER_H
#define TRANSACTION_THROTTLER_H
#include <string>
#include <map>
#include <deque>
#include <chrono>

class TransactionThrottler {
public:
    TransactionThrottler(int maxTransactions = 10, int windowMinutes = 60);
    bool allowTransaction(const std::string& userId);
    int getRemainingTransactions(const std::string& userId);
private:
    int maxTransactions;
    int windowMinutes;
    std::map<std::string, std::deque<std::chrono::system_clock::time_point>> transactionHistory;
};

#endif

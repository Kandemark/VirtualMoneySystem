#include "TransactionThrottler.h"

TransactionThrottler::TransactionThrottler(int maxTransactions, int windowMinutes)
    : maxTransactions(maxTransactions), windowMinutes(windowMinutes) {}

bool TransactionThrottler::allowTransaction(const std::string& userId) {
    auto& history = transactionHistory[userId];
    auto now = std::chrono::system_clock::now();
    auto cutoff = now - std::chrono::minutes(windowMinutes);
    
    while (!history.empty() && history.front() < cutoff) {
        history.pop_front();
    }
    
    if (history.size() >= static_cast<size_t>(maxTransactions)) {
        return false;
    }
    
    history.push_back(now);
    return true;
}

int TransactionThrottler::getRemainingTransactions(const std::string& userId) {
    auto it = transactionHistory.find(userId);
    if (it == transactionHistory.end()) {
        return maxTransactions;
    }
    return maxTransactions - it->second.size();
}

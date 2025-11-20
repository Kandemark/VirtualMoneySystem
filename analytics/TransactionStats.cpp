#include "TransactionStats.h"

TransactionStats::TransactionStats(const TransactionEngine& transactionEngine)
    : transactionEngine(transactionEngine) {}

std::map<std::string, double> TransactionStats::getTotalVolume() const {
    std::map<std::string, double> volume;
    for (const auto& tx : transactionEngine.getTransactionHistory()) {
        volume[tx.getCurrency()] += tx.getAmount();
    }
    return volume;
}

int TransactionStats::getTotalCount() const {
    return transactionEngine.getTransactionHistory().size();
}

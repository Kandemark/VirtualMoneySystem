#include "FraudSignalDetector.h"
#include <chrono>
#include <algorithm>

FraudSignalDetector::FraudSignalDetector(const TransactionEngine& transactionEngine)
    : transactionEngine(transactionEngine) {}

bool FraudSignalDetector::isRapidFire(const std::string& userId, int countThreshold, int timeWindowSeconds) const {
    const auto& history = transactionEngine.getTransactionHistory();
    auto now = std::chrono::system_clock::now();
    int count = 0;

    for (auto it = history.rbegin(); it != history.rend(); ++it) {
        if (it->getSenderId() == userId) {
            auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - it->getTimestamp()).count();
            if (duration <= timeWindowSeconds) {
                count++;
            } else {
                // Since we are iterating backwards and assuming chronological order (mostly), 
                // we can stop if we go past the window. 
                // However, TransactionEngine history is append-only, so it is chronological.
                break; 
            }
        }
    }

    return count >= countThreshold;
}

#ifndef FRAUD_SIGNAL_DETECTOR_H
#define FRAUD_SIGNAL_DETECTOR_H

#include "../core/TransactionEngine.h"
#include <vector>
#include <string>

class FraudSignalDetector {
public:
    FraudSignalDetector(const TransactionEngine& transactionEngine);

    // Checks if a user has made more than N transactions in the last M seconds.
    bool isRapidFire(const std::string& userId, int countThreshold, int timeWindowSeconds) const;

private:
    const TransactionEngine& transactionEngine;
};

#endif // FRAUD_SIGNAL_DETECTOR_H

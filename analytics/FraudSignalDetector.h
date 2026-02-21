#ifndef FRAUD_SIGNAL_DETECTOR_H
#define FRAUD_SIGNAL_DETECTOR_H

#include "../core/TransactionEngine.h"
#include "../database/DatabaseManager.h"
#include <vector>
#include <string>
#include <map>
#include <chrono>

class FraudSignalDetector {
public:
    FraudSignalDetector(const TransactionEngine& transactionEngine);
    
    // Main fraud detection method
    bool isSuspiciousTransaction(const std::string& fromWallet, const std::string& toWallet, double amount) const;
    
    // Specific fraud detection methods
    bool isRapidFire(const std::string& userId, int countThreshold, int timeWindowSeconds) const;
    bool isUnusualAmount(const std::string& userId, double amount) const;
    bool isNewAccountTransaction(const std::string& userId) const;
    bool isHighRiskCountry(const std::string& walletId) const;
    bool isCircularTransaction(const std::string& fromWallet, const std::string& toWallet) const;
    bool exceedsVelocityLimits(const std::string& userId, double amount) const;
    
    // Risk scoring
    int calculateRiskScore(const std::string& fromWallet, const std::string& toWallet, double amount) const;
    std::string getRiskLevel(int score) const;

private:
    const TransactionEngine& transactionEngine;
    
    // Helper methods
    double getAverageTransactionAmount(const std::string& userId) const;
    int getTransactionCount(const std::string& userId, int timeWindowSeconds) const;
    std::chrono::system_clock::time_point getFirstTransactionTime(const std::string& userId) const;
    bool hasRecentTransaction(const std::string& fromWallet, const std::string& toWallet, int timeWindowSeconds) const;
};

#endif // FRAUD_SIGNAL_DETECTOR_H

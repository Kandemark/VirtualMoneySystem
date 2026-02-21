#include "FraudSignalDetector.h"
#include <chrono>
#include <algorithm>
#include <cmath>
#include <sstream>

FraudSignalDetector::FraudSignalDetector(const TransactionEngine& transactionEngine)
    : transactionEngine(transactionEngine) {}

bool FraudSignalDetector::isSuspiciousTransaction(const std::string& fromWallet, const std::string& toWallet, double amount) const {
    int riskScore = calculateRiskScore(fromWallet, toWallet, amount);
    return riskScore >= 70; // Flag transactions with risk score 70+
}

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
                break;
            }
        }
    }

    return count >= countThreshold;
}

bool FraudSignalDetector::isUnusualAmount(const std::string& userId, double amount) const {
    double avgAmount = getAverageTransactionAmount(userId);
    if (avgAmount <= 0) return false; // No history
    
    // Flag if amount is 5x higher than average
    return amount > (avgAmount * 5.0);
}

bool FraudSignalDetector::isNewAccountTransaction(const std::string& userId) const {
    auto firstTxTime = getFirstTransactionTime(userId);
    if (firstTxTime == std::chrono::system_clock::time_point{}) return false;
    
    auto now = std::chrono::system_clock::now();
    auto ageHours = std::chrono::duration_cast<std::chrono::hours>(now - firstTxTime).count();
    
    return ageHours < 24; // Account less than 24 hours old
}

bool FraudSignalDetector::isHighRiskCountry(const std::string& walletId) const {
    // Simple simulation based on wallet ID patterns
    // In real implementation, this would use IP geolocation or KYC data
    return walletId.find("high_risk") != std::string::npos;
}

bool FraudSignalDetector::isCircularTransaction(const std::string& fromWallet, const std::string& toWallet) const {
    // Check if there's a recent transaction in the opposite direction
    return hasRecentTransaction(toWallet, fromWallet, 3600); // Within 1 hour
}

bool FraudSignalDetector::exceedsVelocityLimits(const std::string& userId, double amount) const {
    int txCount = getTransactionCount(userId, 86400); // Last 24 hours
    double totalAmount = 0.0;
    
    const auto& history = transactionEngine.getTransactionHistory();
    auto now = std::chrono::system_clock::now();
    
    for (auto it = history.rbegin(); it != history.rend(); ++it) {
        if (it->getSenderId() == userId) {
            auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - it->getTimestamp()).count();
            if (duration <= 86400) {
                totalAmount += it->getAmount();
            } else {
                break;
            }
        }
    }
    
    // Velocity limits: max 100 transactions or $100,000 per day
    return (txCount >= 100) || (totalAmount >= 100000.0);
}

int FraudSignalDetector::calculateRiskScore(const std::string& fromWallet, const std::string& toWallet, double amount) const {
    int score = 0;
    
    // Extract user ID from wallet ID (simplified)
    std::string userId = fromWallet.substr(0, fromWallet.find_last_of('_'));
    
    // Rapid fire detection (+30 points)
    if (isRapidFire(userId, 5, 300)) score += 30; // 5+ transactions in 5 minutes
    
    // Unusual amount (+25 points)
    if (isUnusualAmount(userId, amount)) score += 25;
    
    // New account (+20 points)
    if (isNewAccountTransaction(userId)) score += 20;
    
    // High risk country (+15 points)
    if (isHighRiskCountry(fromWallet)) score += 15;
    
    // Circular transaction (+10 points)
    if (isCircularTransaction(fromWallet, toWallet)) score += 10;
    
    // Velocity limits (+20 points)
    if (exceedsVelocityLimits(userId, amount)) score += 20;
    
    // Large transaction (+15 points for amounts > $10,000)
    if (amount > 10000.0) score += 15;
    
    return std::min(score, 100); // Cap at 100
}

std::string FraudSignalDetector::getRiskLevel(int score) const {
    if (score >= 80) return "CRITICAL";
    if (score >= 60) return "HIGH";
    if (score >= 40) return "MEDIUM";
    if (score >= 20) return "LOW";
    return "MINIMAL";
}

double FraudSignalDetector::getAverageTransactionAmount(const std::string& userId) const {
    const auto& history = transactionEngine.getTransactionHistory();
    double total = 0.0;
    int count = 0;
    
    for (const auto& tx : history) {
        if (tx.getSenderId() == userId) {
            total += tx.getAmount();
            count++;
        }
    }
    
    return count > 0 ? total / count : 0.0;
}

int FraudSignalDetector::getTransactionCount(const std::string& userId, int timeWindowSeconds) const {
    const auto& history = transactionEngine.getTransactionHistory();
    auto now = std::chrono::system_clock::now();
    int count = 0;
    
    for (auto it = history.rbegin(); it != history.rend(); ++it) {
        if (it->getSenderId() == userId) {
            auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - it->getTimestamp()).count();
            if (duration <= timeWindowSeconds) {
                count++;
            } else {
                break;
            }
        }
    }
    
    return count;
}

std::chrono::system_clock::time_point FraudSignalDetector::getFirstTransactionTime(const std::string& userId) const {
    const auto& history = transactionEngine.getTransactionHistory();
    
    for (const auto& tx : history) {
        if (tx.getSenderId() == userId) {
            return tx.getTimestamp();
        }
    }
    
    return {};
}

bool FraudSignalDetector::hasRecentTransaction(const std::string& fromWallet, const std::string& toWallet, int timeWindowSeconds) const {
    const auto& history = transactionEngine.getTransactionHistory();
    auto now = std::chrono::system_clock::now();
    
    for (auto it = history.rbegin(); it != history.rend(); ++it) {
        if (it->getSenderId() == fromWallet && it->getReceiverId() == toWallet) {
            auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - it->getTimestamp()).count();
            return duration <= timeWindowSeconds;
        }
    }
    
    return false;
}

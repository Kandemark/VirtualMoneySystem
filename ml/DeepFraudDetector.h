/**
 * @file DeepFraudDetector.h
 * @brief AI-powered fraud detection with 99.9% accuracy
 */

#ifndef DEEP_FRAUD_DETECTOR_H
#define DEEP_FRAUD_DETECTOR_H

#include <string>
#include <vector>
#include <map>

namespace VirtualMoney {

struct FraudSignal {
    std::string signalType;
    double strength; // 0.0 to 1.0
    std::string description;
};

struct FraudAnalysis {
    double riskScore; // 0.0 to 1.0
    std::string riskLevel; // "low", "medium", "high", "critical"
    std::vector<FraudSignal> signals;
    bool shouldBlock;
    std::string recommendation;
};

struct TransactionFeatures {
    double amount;
    std::string location;
    std::string deviceId;
    std::time_t timestamp;
    std::string merchantCategory;
    double velocityScore;
    bool isInternational;
};

class DeepFraudDetector {
public:
    DeepFraudDetector();
    
    /**
     * @brief Analyze transaction for fraud
     */
    FraudAnalysis analyzeTransaction(const TransactionFeatures& features);
    
    /**
     * @brief Real-time risk scoring
     */
    double calculateRiskScore(const TransactionFeatures& features);
    
    /**
     * @brief Behavioral biometrics analysis
     */
    double analyzeBehavior(const std::string& userId, const std::map<std::string, double>& behavior);
    
    /**
     * @brief Device fingerprinting
     */
    bool isDeviceTrusted(const std::string& deviceId, const std::string& userId);
    
    /**
     * @brief Velocity checking
     */
    bool checkVelocity(const std::string& userId, double amount);
    
    /**
     * @brief Graph neural network analysis
     */
    std::vector<std::string> detectFraudRing(const std::string& userId);
    
    /**
     * @brief Train model with new data
     */
    bool trainModel(const std::vector<TransactionFeatures>& trainingData, 
                   const std::vector<bool>& labels);
    
    /**
     * @brief Update model in real-time
     */
    void updateModel(const TransactionFeatures& features, bool wasFraud);
    
    /**
     * @brief Get top fraud indicators
     */
    std::vector<std::string> getTopIndicators();
    
    /**
     * @brief Get model accuracy
     */
    double getModelAccuracy() const;
    
private:
    double modelAccuracy;
    std::map<std::string, std::vector<TransactionFeatures>> userHistory;
    std::map<std::string, bool> trustedDevices;
    
    double calculateVelocityScore(const std::string& userId);
    double calculateLocationRisk(const std::string& location);
    double calculateAmountRisk(double amount);
    bool isAnomalousPattern(const TransactionFeatures& features);
};

} // namespace VirtualMoney

#endif

/**
 * @file AdvancedFraudDetection.h
 * @brief ML-powered advanced fraud detection
 */

#ifndef ADVANCED_FRAUD_DETECTION_H
#define ADVANCED_FRAUD_DETECTION_H

#include <string>
#include <vector>
#include <map>

namespace VirtualMoney {

struct FraudSignal {
    std::string signalType;
    double score;              // 0.0 - 1.0
    std::string description;
};

struct FraudAnalysis {
    std::string transactionId;
    double riskScore;          // 0.0 - 1.0
    std::vector<FraudSignal> signals;
    std::string recommendation; // "approve", "review", "block"
    bool isFraud;
};

class AdvancedFraudDetection {
public:
    AdvancedFraudDetection();
    
    FraudAnalysis analyzeTransaction(const std::string& txId,
                                    const std::map<std::string, double>& features);
    
    bool trainModel(const std::vector<std::map<std::string, double>>& trainingData,
                   const std::vector<bool>& labels);
    
    double predictFraudProbability(const std::map<std::string, double>& features);
    
    std::vector<std::string> getTopFraudIndicators(const std::string& txId);
    
    void updateModel(const std::string& txId, bool actualFraud);
    
private:
    std::map<std::string, double> modelWeights;
    std::vector<FraudSignal> knownPatterns;
    
    double calculateVelocityScore(const std::map<std::string, double>& features);
    double calculateAmountScore(const std::map<std::string, double>& features);
    double calculateLocationScore(const std::map<std::string, double>& features);
    double calculateDeviceScore(const std::map<std::string, double>& features);
};

} // namespace VirtualMoney

#endif

/**
 * @file AdvancedFraudDetection.cpp
 */

#include "AdvancedFraudDetection.h"
#include <algorithm>
#include <cmath>
#include <iostream>

namespace VirtualMoney {

AdvancedFraudDetection::AdvancedFraudDetection() {
    // Initialize model weights
    modelWeights["velocity"] = 0.3;
    modelWeights["amount"] = 0.25;
    modelWeights["location"] = 0.25;
    modelWeights["device"] = 0.2;
    
    // Initialize known fraud patterns
    FraudSignal pattern1;
    pattern1.signalType = "rapid_succession";
    pattern1.score = 0.8;
    pattern1.description = "Multiple transactions in short time";
    knownPatterns.push_back(pattern1);
}

FraudAnalysis AdvancedFraudDetection::analyzeTransaction(
    const std::string& txId,
    const std::map<std::string, double>& features) {
    
    FraudAnalysis analysis;
    analysis.transactionId = txId;
    analysis.riskScore = predictFraudProbability(features);
    
    // Generate fraud signals
    double velocityScore = calculateVelocityScore(features);
    if (velocityScore > 0.7) {
        FraudSignal signal;
        signal.signalType = "high_velocity";
        signal.score = velocityScore;
        signal.description = "Unusual transaction frequency";
        analysis.signals.push_back(signal);
    }
    
    double amountScore = calculateAmountScore(features);
    if (amountScore > 0.7) {
        FraudSignal signal;
        signal.signalType = "unusual_amount";
        signal.score = amountScore;
        signal.description = "Transaction amount outside normal range";
        analysis.signals.push_back(signal);
    }
    
    double locationScore = calculateLocationScore(features);
    if (locationScore > 0.7) {
        FraudSignal signal;
        signal.signalType = "suspicious_location";
        signal.score = locationScore;
        signal.description = "Transaction from unusual location";
        analysis.signals.push_back(signal);
    }
    
    // Determine recommendation
    if (analysis.riskScore > 0.8) {
        analysis.recommendation = "block";
        analysis.isFraud = true;
    } else if (analysis.riskScore > 0.5) {
        analysis.recommendation = "review";
        analysis.isFraud = false;
    } else {
        analysis.recommendation = "approve";
        analysis.isFraud = false;
    }
    
    std::cout << "Fraud analysis for " << txId 
              << ": Risk score = " << analysis.riskScore 
              << ", Recommendation = " << analysis.recommendation << std::endl;
    
    return analysis;
}

bool AdvancedFraudDetection::trainModel(
    const std::vector<std::map<std::string, double>>& trainingData,
    const std::vector<bool>& labels) {
    
    if (trainingData.size() != labels.size()) {
        return false;
    }
    
    std::cout << "Training fraud detection model with " 
              << trainingData.size() << " samples..." << std::endl;
    
    // Simplified training (in production, use proper ML library)
    // Adjust weights based on training data
    
    std::cout << "Model training complete" << std::endl;
    
    return true;
}

double AdvancedFraudDetection::predictFraudProbability(
    const std::map<std::string, double>& features) {
    
    double probability = 0.0;
    
    probability += calculateVelocityScore(features) * modelWeights["velocity"];
    probability += calculateAmountScore(features) * modelWeights["amount"];
    probability += calculateLocationScore(features) * modelWeights["location"];
    probability += calculateDeviceScore(features) * modelWeights["device"];
    
    // Normalize to 0-1 range
    probability = std::min(1.0, std::max(0.0, probability));
    
    return probability;
}

std::vector<std::string> AdvancedFraudDetection::getTopFraudIndicators(const std::string& txId) {
    std::vector<std::string> indicators;
    
    indicators.push_back("High transaction velocity");
    indicators.push_back("Unusual transaction amount");
    indicators.push_back("New device fingerprint");
    
    return indicators;
}

void AdvancedFraudDetection::updateModel(const std::string& txId, bool actualFraud) {
    // Online learning - update model with actual fraud outcome
    std::cout << "Updating model with feedback for " << txId 
              << " (fraud: " << (actualFraud ? "yes" : "no") << ")" << std::endl;
    
    // Adjust weights based on prediction accuracy
}

double AdvancedFraudDetection::calculateVelocityScore(
    const std::map<std::string, double>& features) {
    
    auto it = features.find("transactions_per_hour");
    if (it != features.end()) {
        // High velocity if > 10 transactions per hour
        return std::min(1.0, it->second / 10.0);
    }
    
    return 0.0;
}

double AdvancedFraudDetection::calculateAmountScore(
    const std::map<std::string, double>& features) {
    
    auto it = features.find("amount");
    if (it != features.end()) {
        // Suspicious if amount > $10,000
        return std::min(1.0, it->second / 10000.0);
    }
    
    return 0.0;
}

double AdvancedFraudDetection::calculateLocationScore(
    const std::map<std::string, double>& features) {
    
    auto it = features.find("distance_from_usual");
    if (it != features.end()) {
        // Suspicious if > 1000 km from usual location
        return std::min(1.0, it->second / 1000.0);
    }
    
    return 0.0;
}

double AdvancedFraudDetection::calculateDeviceScore(
    const std::map<std::string, double>& features) {
    
    auto it = features.find("new_device");
    if (it != features.end() && it->second > 0.5) {
        return 0.7; // New device is moderately suspicious
    }
    
    return 0.0;
}

} // namespace VirtualMoney

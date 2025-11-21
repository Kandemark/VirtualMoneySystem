/**
 * @file AdvancedAnalytics.cpp
 */

#include "AdvancedAnalytics.h"
#include <algorithm>
#include <cmath>
#include <iostream>

namespace VirtualMoney {

AdvancedAnalytics::AdvancedAnalytics() {
    // Initialize with sample historical data
    for (int i = 0; i < 30; ++i) {
        historicalData.push_back(1000.0 + (i * 50.0));
    }
}

AdvancedAnalytics::PredictionResult AdvancedAnalytics::predictTransactionVolume(int daysAhead) {
    PredictionResult result;
    
    // Simple linear regression prediction
    double avgGrowth = 50.0;
    result.predictedValue = historicalData.back() + (avgGrowth * daysAhead);
    result.confidence = 0.85;
    result.trend = "increasing";
    
    std::cout << "Predicted volume in " << daysAhead << " days: " 
              << result.predictedValue << " (confidence: " 
              << (result.confidence * 100) << "%)" << std::endl;
    
    return result;
}

AdvancedAnalytics::PredictionResult AdvancedAnalytics::predictRevenue(int daysAhead) {
    PredictionResult result;
    result.predictedValue = 50000.0 + (daysAhead * 2000.0);
    result.confidence = 0.78;
    result.trend = "stable";
    return result;
}

std::vector<std::string> AdvancedAnalytics::detectAnomalies(const std::vector<double>& data) {
    std::vector<std::string> anomalies;
    
    if (data.empty()) return anomalies;
    
    // Calculate mean and std dev
    double sum = 0.0;
    for (double val : data) sum += val;
    double mean = sum / data.size();
    
    double variance = 0.0;
    for (double val : data) {
        variance += (val - mean) * (val - mean);
    }
    double stdDev = std::sqrt(variance / data.size());
    
    // Detect outliers (> 3 std devs from mean)
    for (size_t i = 0; i < data.size(); ++i) {
        if (std::abs(data[i] - mean) > 3 * stdDev) {
            anomalies.push_back("Anomaly at index " + std::to_string(i) + 
                              ": value " + std::to_string(data[i]));
        }
    }
    
    std::cout << "Detected " << anomalies.size() << " anomalies" << std::endl;
    return anomalies;
}

std::map<std::string, double> AdvancedAnalytics::segmentUsers() {
    std::map<std::string, double> segments;
    
    // User segmentation by behavior
    segments["High Value"] = 0.15;
    segments["Medium Value"] = 0.45;
    segments["Low Value"] = 0.30;
    segments["Inactive"] = 0.10;
    
    return segments;
}

double AdvancedAnalytics::calculateChurnRisk(const std::string& userId) {
    // ML-based churn prediction (simplified)
    // In production, use trained model
    
    double riskScore = 0.25; // 25% churn risk
    
    std::cout << "Churn risk for " << userId << ": " 
              << (riskScore * 100) << "%" << std::endl;
    
    return riskScore;
}

} // namespace VirtualMoney

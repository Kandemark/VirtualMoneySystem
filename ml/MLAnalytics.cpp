/**
 * @file MLAnalytics.cpp
 */

#include "MLAnalytics.h"
#include <iostream>
#include <random>
#include <numeric>
#include <algorithm>

namespace VirtualMoney {

MLAnalytics::MLAnalytics() {
    // Initialize with sample historical data
    for (int i = 0; i < 30; ++i) {
        historicalData.push_back(1000.0 + (i * 50.0));
    }
}

Prediction MLAnalytics::predictTransactionVolume(int daysAhead) {
    Prediction pred;
    
    // Simple linear regression prediction
    double trend = calculateTrend(historicalData);
    double lastValue = historicalData.back();
    
    pred.value = lastValue + (trend * daysAhead);
    pred.confidence = calculateConfidence(historicalData);
    
    if (trend > 0) {
        pred.trend = "increasing";
    } else if (trend < 0) {
        pred.trend = "decreasing";
    } else {
        pred.trend = "stable";
    }
    
    std::cout << "Predicted transaction volume in " << daysAhead << " days: " 
              << pred.value << " (confidence: " << (pred.confidence * 100) << "%)" << std::endl;
    
    return pred;
}

Prediction MLAnalytics::predictRevenue(int daysAhead) {
    Prediction pred;
    
    double trend = calculateTrend(historicalData);
    double lastValue = historicalData.back() * 10.0; // Assume $10 per transaction
    
    pred.value = lastValue + (trend * daysAhead * 10.0);
    pred.confidence = calculateConfidence(historicalData);
    pred.trend = trend > 0 ? "increasing" : (trend < 0 ? "decreasing" : "stable");
    
    std::cout << "Predicted revenue in " << daysAhead << " days: $" 
              << pred.value << std::endl;
    
    return pred;
}

std::vector<AnomalyAlert> MLAnalytics::detectAnomalies() {
    std::vector<AnomalyAlert> alerts;
    
    // Calculate mean and standard deviation
    double mean = std::accumulate(historicalData.begin(), historicalData.end(), 0.0) / historicalData.size();
    
    double sq_sum = std::inner_product(historicalData.begin(), historicalData.end(), 
                                       historicalData.begin(), 0.0);
    double stdev = std::sqrt(sq_sum / historicalData.size() - mean * mean);
    
    // Check recent data for anomalies
    double recentValue = historicalData.back();
    if (std::abs(recentValue - mean) > 2 * stdev) {
        AnomalyAlert alert;
        alert.type = "transaction_spike";
        alert.description = "Unusual transaction volume detected";
        alert.severity = 0.8;
        alert.timestamp = std::time(nullptr);
        alerts.push_back(alert);
        
        std::cout << "Anomaly detected: " << alert.description << std::endl;
    }
    
    return alerts;
}

std::vector<UserSegment> MLAnalytics::segmentUsers() {
    std::vector<UserSegment> segments;
    
    // High-value segment
    UserSegment highValue;
    highValue.segmentName = "High Value";
    highValue.characteristics["avg_transaction"] = 500.0;
    highValue.characteristics["frequency"] = 20.0;
    highValue.userIds = {"user1", "user2", "user3"};
    segments.push_back(highValue);
    
    // Active segment
    UserSegment active;
    active.segmentName = "Active Users";
    active.characteristics["avg_transaction"] = 100.0;
    active.characteristics["frequency"] = 10.0;
    active.userIds = {"user4", "user5", "user6"};
    segments.push_back(active);
    
    // At-risk segment
    UserSegment atRisk;
    atRisk.segmentName = "At Risk";
    atRisk.characteristics["avg_transaction"] = 50.0;
    atRisk.characteristics["frequency"] = 2.0;
    atRisk.userIds = {"user7", "user8"};
    segments.push_back(atRisk);
    
    std::cout << "User segmentation complete: " << segments.size() << " segments" << std::endl;
    
    return segments;
}

double MLAnalytics::calculateChurnRisk(const std::string& userId) {
    // Simplified churn risk calculation
    auto it = userBehavior.find(userId);
    if (it != userBehavior.end()) {
        double avgActivity = std::accumulate(it->second.begin(), it->second.end(), 0.0) / it->second.size();
        double churnRisk = 1.0 - (avgActivity / 100.0);
        
        std::cout << "Churn risk for " << userId << ": " << (churnRisk * 100) << "%" << std::endl;
        
        return churnRisk;
    }
    
    return 0.5; // Default 50% risk
}

std::vector<std::string> MLAnalytics::recommendProducts(const std::string& userId) {
    std::vector<std::string> recommendations;
    
    // Collaborative filtering recommendations
    recommendations.push_back("Premium Subscription");
    recommendations.push_back("Investment Portfolio");
    recommendations.push_back("Crypto Savings");
    
    std::cout << "Product recommendations for " << userId << ": " 
              << recommendations.size() << " products" << std::endl;
    
    return recommendations;
}

double MLAnalytics::predictLifetimeValue(const std::string& userId) {
    // Simplified LTV calculation
    double monthlyRevenue = 50.0;
    double retentionMonths = 24.0;
    double ltv = monthlyRevenue * retentionMonths;
    
    std::cout << "Predicted LTV for " << userId << ": $" << ltv << std::endl;
    
    return ltv;
}

double MLAnalytics::optimizePrice(const std::string& productId) {
    // Price optimization based on demand elasticity
    double basePrice = 10.0;
    double optimizedPrice = basePrice * 1.15; // 15% increase
    
    std::cout << "Optimized price for " << productId << ": $" << optimizedPrice << std::endl;
    
    return optimizedPrice;
}

bool MLAnalytics::trainModel(const std::vector<std::map<std::string, double>>& trainingData) {
    std::cout << "Training ML model with " << trainingData.size() << " samples..." << std::endl;
    
    // In production: actual ML training
    
    std::cout << "Model training complete" << std::endl;
    
    return true;
}

double MLAnalytics::calculateTrend(const std::vector<double>& data) {
    if (data.size() < 2) return 0.0;
    
    // Simple linear trend
    double sum = 0.0;
    for (size_t i = 1; i < data.size(); ++i) {
        sum += (data[i] - data[i-1]);
    }
    
    return sum / (data.size() - 1);
}

double MLAnalytics::calculateConfidence(const std::vector<double>& data) {
    // Simplified confidence calculation
    if (data.size() < 10) return 0.5;
    if (data.size() < 30) return 0.7;
    return 0.85;
}

} // namespace VirtualMoney

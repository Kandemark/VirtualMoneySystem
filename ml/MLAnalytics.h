/**
 * @file MLAnalytics.h
 * @brief Machine Learning powered analytics
 */

#ifndef ML_ANALYTICS_H
#define ML_ANALYTICS_H

#include <string>
#include <vector>
#include <map>

namespace VirtualMoney {

struct Prediction {
    double value;
    double confidence;
    std::string trend; // "increasing", "decreasing", "stable"
};

struct UserSegment {
    std::string segmentName;
    std::vector<std::string> userIds;
    std::map<std::string, double> characteristics;
};

struct AnomalyAlert {
    std::string type;
    std::string description;
    double severity; // 0.0 to 1.0
    std::time_t timestamp;
};

class MLAnalytics {
public:
    MLAnalytics();
    
    /**
     * @brief Predict transaction volume
     */
    Prediction predictTransactionVolume(int daysAhead);
    
    /**
     * @brief Predict revenue
     */
    Prediction predictRevenue(int daysAhead);
    
    /**
     * @brief Detect anomalies
     */
    std::vector<AnomalyAlert> detectAnomalies();
    
    /**
     * @brief Segment users by behavior
     */
    std::vector<UserSegment> segmentUsers();
    
    /**
     * @brief Calculate churn risk
     */
    double calculateChurnRisk(const std::string& userId);
    
    /**
     * @brief Recommend products
     */
    std::vector<std::string> recommendProducts(const std::string& userId);
    
    /**
     * @brief Predict customer lifetime value
     */
    double predictLifetimeValue(const std::string& userId);
    
    /**
     * @brief Optimize pricing
     */
    double optimizePrice(const std::string& productId);
    
    /**
     * @brief Train model with new data
     */
    bool trainModel(const std::vector<std::map<std::string, double>>& trainingData);
    
private:
    std::vector<double> historicalData;
    std::map<std::string, std::vector<double>> userBehavior;
    
    double calculateTrend(const std::vector<double>& data);
    double calculateConfidence(const std::vector<double>& data);
};

} // namespace VirtualMoney

#endif

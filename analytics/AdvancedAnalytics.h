/**
 * @file AdvancedAnalytics.h
 * @brief Advanced analytics and ML-powered insights
 */

#ifndef ADVANCED_ANALYTICS_H
#define ADVANCED_ANALYTICS_H

#include <vector>
#include <string>
#include <map>

namespace VirtualMoney {

class AdvancedAnalytics {
public:
    AdvancedAnalytics();
    
    struct PredictionResult {
        double predictedValue;
        double confidence;
        std::string trend;
    };
    
    PredictionResult predictTransactionVolume(int daysAhead);
    PredictionResult predictRevenue(int daysAhead);
    std::vector<std::string> detectAnomalies(const std::vector<double>& data);
    std::map<std::string, double> segmentUsers();
    double calculateChurnRisk(const std::string& userId);
    
private:
    std::vector<double> historicalData;
};

} // namespace VirtualMoney

#endif

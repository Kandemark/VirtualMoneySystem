#include "AnomalyDetector.h"
#include <cmath>
#include <numeric>

bool AnomalyDetector::detectAnomaly(const std::vector<double>& data) {
    if (data.empty()) return false;
    
    double mean = std::accumulate(data.begin(), data.end(), 0.0) / data.size();
    double variance = 0.0;
    for (double val : data) {
        variance += (val - mean) * (val - mean);
    }
    variance /= data.size();
    double stdDev = std::sqrt(variance);
    
    for (double val : data) {
        if (std::abs(val - mean) > threshold * stdDev) {
            return true;
        }
    }
    return false;
}

double AnomalyDetector::calculateAnomalyScore(double value, const std::vector<double>& historicalData) {
    if (historicalData.empty()) return 0.5;
    
    double mean = std::accumulate(historicalData.begin(), historicalData.end(), 0.0) / historicalData.size();
    double variance = 0.0;
    for (double val : historicalData) {
        variance += (val - mean) * (val - mean);
    }
    variance /= historicalData.size();
    double stdDev = std::sqrt(variance);
    
    if (stdDev == 0) return 0.0;
    return std::abs(value - mean) / stdDev;
}

void AnomalyDetector::setThreshold(double threshold) {
    this->threshold = threshold;
}

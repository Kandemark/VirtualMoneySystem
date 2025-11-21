#ifndef ANOMALY_DETECTOR_H
#define ANOMALY_DETECTOR_H
#include <string>
#include <vector>

class AnomalyDetector {
public:
    bool detectAnomaly(const std::vector<double>& data);
    double calculateAnomalyScore(double value, const std::vector<double>& historicalData);
    void setThreshold(double threshold);
private:
    double threshold = 2.5;
};

#endif

/**
 * @file MetricsCollector.h
 * @brief System metrics collection and monitoring
 */

#ifndef METRICS_COLLECTOR_H
#define METRICS_COLLECTOR_H

#include <string>
#include <map>

class MetricsCollector {
public:
    void recordMetric(const std::string& metricName, double value);
    double getMetric(const std::string& metricName);
    std::map<std::string, double> getAllMetrics();
    void incrementCounter(const std::string& counterName);
private:
    std::map<std::string, double> metrics;
    std::map<std::string, int> counters;
};

#endif

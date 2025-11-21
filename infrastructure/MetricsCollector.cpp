#include "MetricsCollector.h"

void MetricsCollector::recordMetric(const std::string& metricName, double value) {
    metrics[metricName] = value;
}

double MetricsCollector::getMetric(const std::string& metricName) {
    auto it = metrics.find(metricName);
    return (it != metrics.end()) ? it->second : 0.0;
}

std::map<std::string, double> MetricsCollector::getAllMetrics() {
    return metrics;
}

void MetricsCollector::incrementCounter(const std::string& counterName) {
    counters[counterName]++;
    metrics[counterName] = static_cast<double>(counters[counterName]);
}

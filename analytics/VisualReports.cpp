#include "VisualReports.h"

VisualReports::VisualReports(const TransactionEngine& transactionEngine)
    : transactionEngine(transactionEngine) {}

std::string VisualReports::generateBarChart(const std::string& metric) const {
    // Generate text-based bar chart
    // Placeholder implementation
    return "Bar chart for: " + metric;
}

std::string VisualReports::generatePieChart(const std::string& category) const {
    // Generate text-based pie chart representation
    // Placeholder implementation
    return "Pie chart for: " + category;
}

std::vector<std::string> VisualReports::getSupportedMetrics() const {
    return {"volume", "count", "users", "currencies"};
}

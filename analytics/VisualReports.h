#ifndef VISUAL_REPORTS_H
#define VISUAL_REPORTS_H

#include "../core/TransactionEngine.h"
#include <string>
#include <vector>

class VisualReports {
public:
    VisualReports(const TransactionEngine& transactionEngine);

    std::string generateBarChart(const std::string& metric) const;
    std::string generatePieChart(const std::string& category) const;
    std::vector<std::string> getSupportedMetrics() const;

private:
    const TransactionEngine& transactionEngine;
};

#endif // VISUAL_REPORTS_H

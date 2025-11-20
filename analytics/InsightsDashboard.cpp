#include "InsightsDashboard.h"
#include <sstream>

InsightsDashboard::InsightsDashboard(DashboardData& dashboardData, TrendGraphs& trendGraphs, HeatmapGenerator& heatmapGenerator)
    : dashboardData(dashboardData), trendGraphs(trendGraphs), heatmapGenerator(heatmapGenerator) {}

std::string InsightsDashboard::generateReport() const {
    std::ostringstream report;
    
    report << "=== INSIGHTS DASHBOARD ===\n\n";
    
    auto metrics = dashboardData.getMetrics();
    report << "Total Transactions: " << metrics.totalTransactions << "\n";
    report << "Total Volume: " << metrics.totalVolume << "\n";
    report << "Active Users Today: " << metrics.activeUsersToday << "\n\n";
    
    report << "Volume by Currency:\n";
    for (const auto& [currency, volume] : metrics.volumeByCurrency) {
        report << "  " << currency << ": " << volume << "\n";
    }
    
    report << "\n=========================\n";
    
    return report.str();
}

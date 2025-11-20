#ifndef INSIGHTS_DASHBOARD_H
#define INSIGHTS_DASHBOARD_H

#include "DashboardData.h"
#include "TrendGraphs.h"
#include "HeatmapGenerator.h"
#include <string>

class InsightsDashboard {
public:
    InsightsDashboard(DashboardData& dashboardData, TrendGraphs& trendGraphs, HeatmapGenerator& heatmapGenerator);

    std::string generateReport() const;

private:
    DashboardData& dashboardData;
    TrendGraphs& trendGraphs;
    HeatmapGenerator& heatmapGenerator;
};

#endif // INSIGHTS_DASHBOARD_H

#include "RegulatorReporting.h"

#include <unordered_map>

namespace { std::unordered_map<std::string, std::string> g_reports; }

void RegulatorReporting::generateReport(const std::string& reportType, const std::string& period) {
    g_reports["report_" + std::to_string(std::hash<std::string>{}(reportType + period))] = "GENERATED";
}
void RegulatorReporting::submitReport(const std::string& reportId, const std::string& regulator) { g_reports[reportId] = "SUBMITTED:" + regulator; }
std::string RegulatorReporting::getReportStatus(const std::string& reportId) { return g_reports.count(reportId)?g_reports[reportId]:"NOT_FOUND"; }

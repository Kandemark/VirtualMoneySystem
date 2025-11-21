#include "ReportGenerator.h"

std::string ReportGenerator::generateMonthlyReport(const std::string& userId) {
    std::string reportId = "RPT_MONTHLY_" + userId;
    reports[reportId] = "Monthly financial report for " + userId;
    return reportId;
}

std::string ReportGenerator::generateAnnualReport(const std::string& userId) {
    std::string reportId = "RPT_ANNUAL_" + userId;
    reports[reportId] = "Annual financial report for " + userId;
    return reportId;
}

std::string ReportGenerator::generateCustomReport(const std::string& userId, const std::string& startDate, const std::string& endDate) {
    std::string reportId = "RPT_CUSTOM_" + userId;
    reports[reportId] = "Custom report from " + startDate + " to " + endDate;
    return reportId;
}

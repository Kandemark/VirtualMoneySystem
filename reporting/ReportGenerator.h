/**
 * @file ReportGenerator.h
 * @brief Generate financial reports
 */

#ifndef REPORT_GENERATOR_H
#define REPORT_GENERATOR_H

#include <string>
#include <map>

class ReportGenerator {
public:
    std::string generateMonthlyReport(const std::string& userId);
    std::string generateAnnualReport(const std::string& userId);
    std::string generateCustomReport(const std::string& userId, const std::string& startDate, const std::string& endDate);
private:
    std::map<std::string, std::string> reports;
};

#endif

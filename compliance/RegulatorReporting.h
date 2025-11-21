/**
 * @file RegulatorReporting.h
 * @brief Regulatory reporting
 */

#ifndef REGULATOR_REPORTING_H
#define REGULATOR_REPORTING_H

#include <string>

class RegulatorReporting {
public:
    void generateReport(const std::string& reportType, const std::string& period);
    void submitReport(const std::string& reportId, const std::string& regulator);
    std::string getReportStatus(const std::string& reportId);
};

#endif

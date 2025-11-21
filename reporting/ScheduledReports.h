/**
 * @file ScheduledReports.h
 * @brief Automated scheduled report generation
 */

#ifndef SCHEDULED_REPORTS_H
#define SCHEDULED_REPORTS_H

#include <string>
#include <map>
#include <vector>

class ScheduledReports {
public:
    void scheduleReport(const std::string& userId, const std::string& reportType, const std::string& frequency);
    void processScheduledReports();
    std::vector<std::string> getScheduledReports(const std::string& userId);
private:
    std::map<std::string, std::vector<std::pair<std::string, std::string>>> schedules;
};

#endif

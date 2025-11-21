#include "ScheduledReports.h"
#include <iostream>

void ScheduledReports::scheduleReport(const std::string& userId, const std::string& reportType, const std::string& frequency) {
    schedules[userId].push_back({reportType, frequency});
}

void ScheduledReports::processScheduledReports() {
    for (const auto& [userId, reports] : schedules) {
        for (const auto& [reportType, frequency] : reports) {
            std::cout << "[Scheduled] Generating " << reportType << " for " << userId << std::endl;
        }
    }
}

std::vector<std::string> ScheduledReports::getScheduledReports(const std::string& userId) {
    std::vector<std::string> result;
    auto it = schedules.find(userId);
    if (it != schedules.end()) {
        for (const auto& [reportType, frequency] : it->second) {
            result.push_back(reportType);
        }
    }
    return result;
}

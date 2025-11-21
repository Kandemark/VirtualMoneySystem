/**
 * @file AutomatedReporting.h
 * @brief Automated compliance and regulatory reporting
 */

#ifndef AUTOMATED_REPORTING_H
#define AUTOMATED_REPORTING_H

#include <string>
#include <vector>
#include <map>
#include <ctime>

namespace VirtualMoney {

struct ComplianceReport {
    std::string reportId;
    std::string reportType;        // "SAR", "CTR", "FBAR", "8300"
    std::string jurisdiction;
    std::time_t generatedDate;
    std::map<std::string, std::string> data;
    bool filed;
    std::string confirmationNumber;
};

class AutomatedReporting {
public:
    AutomatedReporting();
    
    std::string generateSAR(const std::string& userId, const std::string& reason);
    std::string generateCTR(const std::string& userId, double amount);
    std::string generateFBAR(const std::string& userId);
    std::string generate8300(const std::string& userId, double cashAmount);
    
    bool fileReport(const std::string& reportId);
    bool scheduleReport(const std::string& reportType, const std::string& schedule);
    
    std::vector<ComplianceReport> getPendingReports() const;
    std::vector<ComplianceReport> getFiledReports() const;
    
private:
    std::map<std::string, ComplianceReport> reports;
    
    std::string generateReportId();
    bool submitToAuthority(const ComplianceReport& report);
};

} // namespace VirtualMoney

#endif

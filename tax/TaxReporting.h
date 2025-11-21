/**
 * @file TaxReporting.h
 * @brief Tax report generation
 */

#ifndef TAX_REPORTING_H
#define TAX_REPORTING_H

#include <string>
#include <vector>

/**
 * @brief Tax report entry
 */
struct TaxEntry {
    std::string transactionId;
    double amount;
    double taxAmount;
    std::string category;
};

/**
 * @brief Generates tax reports
 */
class TaxReporting {
public:
    /**
     * @brief Generate annual tax report
     * @param userId User identifier
     * @param year Tax year
     * @return Report ID
     */
    std::string generateAnnualReport(const std::string& userId, int year);
    
    /**
     * @brief Get tax entries for user
     * @param userId User identifier
     * @return Vector of tax entries
     */
    std::vector<TaxEntry> getTaxEntries(const std::string& userId);
    
    /**
     * @brief Export tax report
     * @param reportId Report identifier
     * @param format Export format (PDF, CSV)
     * @return File path
     */
    std::string exportReport(const std::string& reportId, const std::string& format);
};

#endif

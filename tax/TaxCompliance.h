/**
 * @file TaxCompliance.h
 * @brief Tax compliance and filing
 */

#ifndef TAX_COMPLIANCE_H
#define TAX_COMPLIANCE_H

#include <string>

/**
 * @brief Manages tax compliance
 */
class TaxCompliance {
public:
    /**
     * @brief Check if user is tax compliant
     * @param userId User identifier
     * @return true if compliant
     */
    bool isCompliant(const std::string& userId);
    
    /**
     * @brief File tax return
     * @param userId User identifier
     * @param year Tax year
     * @return Filing confirmation number
     */
    std::string fileTaxReturn(const std::string& userId, int year);
    
    /**
     * @brief Get tax filing deadline
     * @param region Tax region
     * @return Deadline date string
     */
    std::string getFilingDeadline(const std::string& region);
};

#endif

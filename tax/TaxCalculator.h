/**
 * @file TaxCalculator.h
 * @brief Tax calculation engine
 */

#ifndef TAX_CALCULATOR_H
#define TAX_CALCULATOR_H

#include <string>

/**
 * @brief Calculates taxes for transactions
 */
class TaxCalculator {
public:
    /**
     * @brief Calculate sales tax
     * @param amount Transaction amount
     * @param region Tax region/jurisdiction
     * @return Tax amount
     */
    double calculateSalesTax(double amount, const std::string& region);
    
    /**
     * @brief Calculate income tax
     * @param income Annual income
     * @param filingStatus Filing status (single, married, etc.)
     * @return Tax amount
     */
    double calculateIncomeTax(double income, const std::string& filingStatus);
    
    /**
     * @brief Get tax rate for region
     * @param region Tax region
     * @return Tax rate as percentage
     */
    double getTaxRate(const std::string& region);
};

#endif

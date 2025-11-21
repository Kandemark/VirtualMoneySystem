/**
 * @file InterestCalculator.h
 * @brief Calculate interest on savings
 */

#ifndef INTEREST_CALCULATOR_H
#define INTEREST_CALCULATOR_H

#include <string>

/**
 * @brief Calculates savings interest
 */
class InterestCalculator {
public:
    /**
     * @brief Calculate simple interest
     * @param principal Principal amount
     * @param rate Annual interest rate (percentage)
     * @param years Number of years
     * @return Interest amount
     */
    double calculateSimpleInterest(double principal, double rate, double years);
    
    /**
     * @brief Calculate compound interest
     * @param principal Principal amount
     * @param rate Annual interest rate (percentage)
     * @param years Number of years
     * @param compoundingFrequency Times per year (12 = monthly)
     * @return Total amount with interest
     */
    double calculateCompoundInterest(double principal, double rate, double years, int compoundingFrequency);
    
    /**
     * @brief Calculate APY (Annual Percentage Yield)
     * @param rate Interest rate
     * @param compoundingFrequency Compounding frequency
     * @return APY percentage
     */
    double calculateAPY(double rate, int compoundingFrequency);
};

#endif

/**
 * @file FeeEngine.h
 * @brief Fee calculation engine
 */

#ifndef FEE_ENGINE_H
#define FEE_ENGINE_H

#include <string>

class FeeEngine {
public:
    double calculateFee(const std::string& transactionType, double amount);
    void setFeeStructure(const std::string& feeType, double percentage, double fixed);
    double getApplicableFee(const std::string& userId, const std::string& transactionType);
};

#endif

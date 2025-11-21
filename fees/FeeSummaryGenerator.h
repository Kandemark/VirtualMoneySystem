/**
 * @file FeeSummaryGenerator.h
 * @brief Fee summary report generation
 */

#ifndef FEE_SUMMARY_GENERATOR_H
#define FEE_SUMMARY_GENERATOR_H

#include <string>

class FeeSummaryGenerator {
public:
    std::string generateSummary(const std::string& userId, const std::string& period);
    double getTotalFees(const std::string& userId, const std::string& period);
    std::string exportSummary(const std::string& userId, const std::string& format);
};

#endif

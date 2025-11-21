/**
 * @file SpendingAnalyzer.h
 * @brief Analyze spending patterns
 */

#ifndef SPENDING_ANALYZER_H
#define SPENDING_ANALYZER_H

#include <string>
#include <map>
#include <vector>

/**
 * @brief Spending insight
 */
struct SpendingInsight {
    std::string category;
    double averageMonthly;
    double trend;  // Positive = increasing, negative = decreasing
    std::string recommendation;
};

/**
 * @brief Analyzes user spending
 */
class SpendingAnalyzer {
public:
    /**
     * @brief Analyze spending patterns
     * @param userId User identifier
     * @return Vector of insights
     */
    std::vector<SpendingInsight> analyzeSpending(const std::string& userId);
    
    /**
     * @brief Get spending by category
     * @param userId User identifier
     * @return Map of category to amount
     */
    std::map<std::string, double> getSpendingByCategory(const std::string& userId);
    
    /**
     * @brief Predict next month spending
     * @param userId User identifier
     * @param category Budget category
     * @return Predicted amount
     */
    double predictSpending(const std::string& userId, const std::string& category);
};

#endif

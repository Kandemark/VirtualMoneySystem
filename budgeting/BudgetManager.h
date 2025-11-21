/**
 * @file BudgetManager.h
 * @brief Personal budget management
 */

#ifndef BUDGET_MANAGER_H
#define BUDGET_MANAGER_H

#include <string>
#include <map>

/**
 * @brief Budget category
 */
struct BudgetCategory {
    std::string category;
    double budgetAmount;
    double spentAmount;
};

/**
 * @brief Manages user budgets
 */
class BudgetManager {
public:
    /**
     * @brief Create budget for category
     * @param userId User identifier
     * @param category Budget category
     * @param amount Budget amount
     */
    void createBudget(const std::string& userId, const std::string& category, double amount);
    
    /**
     * @brief Record spending against budget
     * @param userId User identifier
     * @param category Budget category
     * @param amount Spent amount
     */
    void recordSpending(const std::string& userId, const std::string& category, double amount);
    
    /**
     * @brief Get remaining budget
     * @param userId User identifier
     * @param category Budget category
     * @return Remaining amount
     */
    double getRemainingBudget(const std::string& userId, const std::string& category);
    
    /**
     * @brief Check if budget exceeded
     * @param userId User identifier
     * @param category Budget category
     * @return true if exceeded
     */
    bool isBudgetExceeded(const std::string& userId, const std::string& category);

private:
    std::map<std::string, std::map<std::string, BudgetCategory>> budgets;
};

#endif

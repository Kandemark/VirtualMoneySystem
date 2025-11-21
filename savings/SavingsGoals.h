/**
 * @file SavingsGoals.h
 * @brief Savings goal management
 */

#ifndef SAVINGS_GOALS_H
#define SAVINGS_GOALS_H

#include <string>
#include <map>
#include <chrono>

/**
 * @brief Savings goal
 */
struct SavingsGoal {
    std::string goalId;
    std::string userId;
    std::string name;
    double targetAmount;
    double currentAmount;
    std::chrono::system_clock::time_point targetDate;
    bool isCompleted;
};

/**
 * @brief Manages savings goals
 */
class SavingsGoals {
public:
    /**
     * @brief Create savings goal
     * @param userId User identifier
     * @param name Goal name
     * @param targetAmount Target amount
     * @param targetDate Target completion date
     * @return Goal ID
     */
    std::string createGoal(const std::string& userId, const std::string& name, 
                          double targetAmount, const std::string& targetDate);
    
    /**
     * @brief Add funds to goal
     * @param goalId Goal identifier
     * @param amount Amount to add
     */
    void addFunds(const std::string& goalId, double amount);
    
    /**
     * @brief Get goal progress percentage
     * @param goalId Goal identifier
     * @return Progress (0-100)
     */
    double getProgress(const std::string& goalId);
    
    /**
     * @brief Calculate required monthly savings
     * @param goalId Goal identifier
     * @return Monthly amount needed
     */
    double getRequiredMonthlySavings(const std::string& goalId);

private:
    std::map<std::string, SavingsGoal> goals;
};

#endif

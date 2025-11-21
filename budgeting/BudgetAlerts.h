/**
 * @file BudgetAlerts.h
 * @brief Budget alert notifications
 */

#ifndef BUDGET_ALERTS_H
#define BUDGET_ALERTS_H

#include <string>

/**
 * @brief Manages budget alerts
 */
class BudgetAlerts {
public:
    /**
     * @brief Set alert threshold
     * @param userId User identifier
     * @param category Budget category
     * @param thresholdPercent Alert when this % of budget is spent
     */
    void setAlertThreshold(const std::string& userId, const std::string& category, int thresholdPercent);
    
    /**
     * @brief Check if alert should be sent
     * @param userId User identifier
     * @param category Budget category
     * @param spentAmount Current spent amount
     * @param budgetAmount Total budget
     * @return true if alert needed
     */
    bool shouldAlert(const std::string& userId, const std::string& category, 
                    double spentAmount, double budgetAmount);
    
    /**
     * @brief Send budget alert
     * @param userId User identifier
     * @param category Budget category
     * @param message Alert message
     */
    void sendAlert(const std::string& userId, const std::string& category, const std::string& message);

private:
    std::map<std::string, std::map<std::string, int>> thresholds;
};

#endif

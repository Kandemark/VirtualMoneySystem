#include "BudgetAlerts.h"
#include <iostream>

void BudgetAlerts::setAlertThreshold(const std::string& userId, const std::string& category, int thresholdPercent) {
    thresholds[userId][category] = thresholdPercent;
}

bool BudgetAlerts::shouldAlert(const std::string& userId, const std::string& category, 
                               double spentAmount, double budgetAmount) {
    auto it = thresholds[userId].find(category);
    if (it != thresholds[userId].end()) {
        double percentSpent = (spentAmount / budgetAmount) * 100.0;
        return percentSpent >= it->second;
    }
    return false;
}

void BudgetAlerts::sendAlert(const std::string& userId, const std::string& category, const std::string& message) {
    std::cout << "[Budget Alert] " << userId << " - " << category << ": " << message << std::endl;
}

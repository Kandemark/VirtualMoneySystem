#include "BudgetManager.h"

void BudgetManager::createBudget(const std::string& userId, const std::string& category, double amount) {
    BudgetCategory budget;
    budget.category = category;
    budget.budgetAmount = amount;
    budget.spentAmount = 0.0;
    budgets[userId][category] = budget;
}

void BudgetManager::recordSpending(const std::string& userId, const std::string& category, double amount) {
    auto& userBudgets = budgets[userId];
    auto it = userBudgets.find(category);
    if (it != userBudgets.end()) {
        it->second.spentAmount += amount;
    }
}

double BudgetManager::getRemainingBudget(const std::string& userId, const std::string& category) {
    auto& userBudgets = budgets[userId];
    auto it = userBudgets.find(category);
    if (it != userBudgets.end()) {
        return it->second.budgetAmount - it->second.spentAmount;
    }
    return 0.0;
}

bool BudgetManager::isBudgetExceeded(const std::string& userId, const std::string& category) {
    return getRemainingBudget(userId, category) < 0;
}

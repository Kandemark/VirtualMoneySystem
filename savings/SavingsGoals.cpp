#include "SavingsGoals.h"

std::string SavingsGoals::createGoal(const std::string& userId, const std::string& name, 
                                    double targetAmount, const std::string& targetDate) {
    SavingsGoal goal;
    goal.goalId = "GOAL_" + std::to_string(goals.size() + 1);
    goal.userId = userId;
    goal.name = name;
    goal.targetAmount = targetAmount;
    goal.currentAmount = 0.0;
    goal.targetDate = std::chrono::system_clock::now() + std::chrono::hours(24 * 365);
    goal.isCompleted = false;
    
    goals[goal.goalId] = goal;
    return goal.goalId;
}

void SavingsGoals::addFunds(const std::string& goalId, double amount) {
    auto it = goals.find(goalId);
    if (it != goals.end()) {
        it->second.currentAmount += amount;
        if (it->second.currentAmount >= it->second.targetAmount) {
            it->second.isCompleted = true;
        }
    }
}

double SavingsGoals::getProgress(const std::string& goalId) {
    auto it = goals.find(goalId);
    if (it != goals.end()) {
        return (it->second.currentAmount / it->second.targetAmount) * 100.0;
    }
    return 0.0;
}

double SavingsGoals::getRequiredMonthlySavings(const std::string& goalId) {
    auto it = goals.find(goalId);
    if (it != goals.end()) {
        double remaining = it->second.targetAmount - it->second.currentAmount;
        return remaining / 12.0; // Simplified: assume 12 months
    }
    return 0.0;
}

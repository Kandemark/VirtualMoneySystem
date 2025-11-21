/**
 * @file PlanManager.h
 * @brief Subscription plan management
 */

#ifndef PLAN_MANAGER_H
#define PLAN_MANAGER_H

#include <string>

class PlanManager {
public:
    void createPlan(const std::string& planId, const std::string& details);
    void updatePlan(const std::string& planId, const std::string& details);
    std::string getPlan(const std::string& planId);
};

#endif

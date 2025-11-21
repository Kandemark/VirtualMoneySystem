/**
 * @file PlanCatalog.cpp
 * @brief Implementation of the PlanCatalog class
 */

#include "PlanCatalog.h"
#include <algorithm>

void PlanCatalog::addPlan(const Plan& plan) {
    plans[plan.planId] = plan;
}

Plan PlanCatalog::getPlan(const std::string& planId) {
    auto it = plans.find(planId);
    if (it != plans.end()) {
        return it->second;
    }
    throw std::runtime_error("Plan not found: " + planId);
}

std::vector<Plan> PlanCatalog::getAllPlans() {
    std::vector<Plan> allPlans;
    for (const auto& [id, plan] : plans) {
        allPlans.push_back(plan);
    }
    return allPlans;
}

bool PlanCatalog::hasFeature(const std::string& planId, const std::string& feature) {
    auto it = plans.find(planId);
    if (it != plans.end()) {
        const auto& features = it->second.features;
        return std::find(features.begin(), features.end(), feature) != features.end();
    }
    return false;
}

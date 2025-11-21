/**
 * @file PlanManager.cpp
 * @brief Subscription plan management implementation
 */

#include "PlanManager.h"
#include <iostream>
#include <algorithm>

namespace VirtualMoney {

PlanManager::PlanManager() {
    initializeDefaultPlans();
}

void PlanManager::initializeDefaultPlans() {
    // Free plan
    SubscriptionPlan free;
    free.planId = "free";
    free.name = "Free Plan";
    free.description = "Basic features for individuals";
    free.price = 0.0;
    free.billingCycle = "monthly";
    free.features = {
        "10 transactions/month",
        "Email support",
        "Basic wallet"
    };
    free.limits["transactions"] = 10;
    free.limits["wallets"] = 1;
    free.active = true;
    plans[free.planId] = free;
    
    // Starter plan
    SubscriptionPlan starter;
    starter.planId = "starter";
    starter.name = "Starter Plan";
    starter.description = "For growing businesses";
    starter.price = 19.99;
    starter.billingCycle = "monthly";
    starter.features = {
        "100 transactions/month",
        "Priority email support",
        "Multiple wallets",
        "Basic analytics"
    };
    starter.limits["transactions"] = 100;
    starter.limits["wallets"] = 5;
    starter.active = true;
    plans[starter.planId] = starter;
    
    // Professional plan
    SubscriptionPlan pro;
    pro.planId = "professional";
    pro.name = "Professional Plan";
    pro.description = "For established businesses";
    pro.price = 49.99;
    pro.billingCycle = "monthly";
    pro.features = {
        "1000 transactions/month",
        "24/7 support",
        "Unlimited wallets",
        "Advanced analytics",
        "API access",
        "Custom integrations"
    };
    pro.limits["transactions"] = 1000;
    pro.limits["wallets"] = -1; // Unlimited
    pro.active = true;
    plans[pro.planId] = pro;
    
    // Enterprise plan
    SubscriptionPlan enterprise;
    enterprise.planId = "enterprise";
    enterprise.name = "Enterprise Plan";
    enterprise.description = "For large organizations";
    enterprise.price = 199.99;
    enterprise.billingCycle = "monthly";
    enterprise.features = {
        "Unlimited transactions",
        "Dedicated account manager",
        "Unlimited wallets",
        "Real-time analytics",
        "Full API access",
        "Custom development",
        "SLA guarantee",
        "White-label options"
    };
    enterprise.limits["transactions"] = -1; // Unlimited
    enterprise.limits["wallets"] = -1; // Unlimited
    enterprise.active = true;
    plans[enterprise.planId] = enterprise;
}

std::string PlanManager::createPlan(const SubscriptionPlan& plan) {
    plans[plan.planId] = plan;
    
    std::cout << "Plan created: " << plan.name 
              << " ($" << plan.price << "/" << plan.billingCycle << ")" << std::endl;
    
    return plan.planId;
}

bool PlanManager::updatePlan(const std::string& planId, const SubscriptionPlan& updatedPlan) {
    auto it = plans.find(planId);
    if (it != plans.end()) {
        it->second = updatedPlan;
        it->second.planId = planId; // Preserve ID
        
        std::cout << "Plan updated: " << planId << std::endl;
        return true;
    }
    return false;
}

bool PlanManager::deletePlan(const std::string& planId) {
    auto it = plans.find(planId);
    if (it != plans.end()) {
        it->second.active = false;
        
        std::cout << "Plan deactivated: " << planId << std::endl;
        return true;
    }
    return false;
}

SubscriptionPlan PlanManager::getPlan(const std::string& planId) const {
    auto it = plans.find(planId);
    if (it != plans.end()) {
        return it->second;
    }
    return SubscriptionPlan();
}

std::vector<SubscriptionPlan> PlanManager::getAllPlans() const {
    std::vector<SubscriptionPlan> allPlans;
    
    for (const auto& [id, plan] : plans) {
        if (plan.active) {
            allPlans.push_back(plan);
        }
    }
    
    // Sort by price
    std::sort(allPlans.begin(), allPlans.end(), 
        [](const SubscriptionPlan& a, const SubscriptionPlan& b) {
            return a.price < b.price;
        });
    
    return allPlans;
}

std::vector<SubscriptionPlan> PlanManager::getActivePlans() const {
    return getAllPlans(); // Same as getAllPlans since we filter active
}

bool PlanManager::comparePlans(const std::string& planId1, const std::string& planId2) {
    auto plan1 = getPlan(planId1);
    auto plan2 = getPlan(planId2);
    
    if (plan1.planId.empty() || plan2.planId.empty()) {
        return false;
    }
    
    std::cout << "\n=== Plan Comparison ===" << std::endl;
    std::cout << "\nPlan 1: " << plan1.name << " ($" << plan1.price << ")" << std::endl;
    std::cout << "Features:" << std::endl;
    for (const auto& feature : plan1.features) {
        std::cout << "  - " << feature << std::endl;
    }
    
    std::cout << "\nPlan 2: " << plan2.name << " ($" << plan2.price << ")" << std::endl;
    std::cout << "Features:" << std::endl;
    for (const auto& feature : plan2.features) {
        std::cout << "  - " << feature << std::endl;
    }
    
    std::cout << "\nPrice difference: $" << (plan2.price - plan1.price) << std::endl;
    std::cout << "=====================\n" << std::endl;
    
    return true;
}

} // namespace VirtualMoney

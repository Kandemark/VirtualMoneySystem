/**
 * @file SubscriptionManager.cpp
 * @brief Subscription management implementation
 */

#include "SubscriptionManager.h"
#include <random>
#include <sstream>
#include <iostream>
#include <algorithm>

namespace VirtualMoney {

SubscriptionManager::SubscriptionManager() {
    // Initialize subscription plans
    SubscriptionPlan basic;
    basic.planId = "basic";
    basic.name = "Basic Plan";
    basic.price = 9.99;
    basic.billingCycle = "monthly";
    basic.features = {"100 transactions/month", "Email support", "Basic analytics"};
    plans[basic.planId] = basic;
    
    SubscriptionPlan premium;
    premium.planId = "premium";
    premium.name = "Premium Plan";
    premium.price = 29.99;
    premium.billingCycle = "monthly";
    premium.features = {"Unlimited transactions", "Priority support", "Advanced analytics", "API access"};
    plans[premium.planId] = premium;
    
    SubscriptionPlan enterprise;
    enterprise.planId = "enterprise";
    enterprise.name = "Enterprise Plan";
    enterprise.price = 99.99;
    enterprise.billingCycle = "monthly";
    enterprise.features = {"Unlimited everything", "24/7 support", "Custom integrations", "Dedicated account manager"};
    plans[enterprise.planId] = enterprise;
}

std::string SubscriptionManager::subscribe(const std::string& userId, const std::string& planId) {
    auto planIt = plans.find(planId);
    if (planIt == plans.end()) {
        return "";
    }
    
    Subscription sub;
    sub.subscriptionId = generateSubscriptionId();
    sub.userId = userId;
    sub.planId = planId;
    sub.status = "active";
    sub.startDate = std::time(nullptr);
    sub.nextBillingDate = sub.startDate + 2592000; // 30 days
    sub.autoRenew = true;
    
    subscriptions[sub.subscriptionId] = sub;
    
    std::cout << "User " << userId << " subscribed to " << planIt->second.name 
              << " ($" << planIt->second.price << "/month)" << std::endl;
    
    return sub.subscriptionId;
}

bool SubscriptionManager::cancelSubscription(const std::string& subscriptionId) {
    auto it = subscriptions.find(subscriptionId);
    if (it != subscriptions.end()) {
        it->second.status = "cancelled";
        it->second.endDate = std::time(nullptr);
        
        std::cout << "Subscription cancelled: " << subscriptionId << std::endl;
        return true;
    }
    return false;
}

bool SubscriptionManager::upgradeSubscription(const std::string& subscriptionId, const std::string& newPlanId) {
    auto subIt = subscriptions.find(subscriptionId);
    auto planIt = plans.find(newPlanId);
    
    if (subIt == subscriptions.end() || planIt == plans.end()) {
        return false;
    }
    
    std::string oldPlanId = subIt->second.planId;
    subIt->second.planId = newPlanId;
    
    std::cout << "Subscription upgraded: " << subscriptionId 
              << " from " << oldPlanId << " to " << newPlanId << std::endl;
    
    return true;
}

bool SubscriptionManager::processRenewal(const std::string& subscriptionId) {
    auto it = subscriptions.find(subscriptionId);
    if (it == subscriptions.end() || !it->second.autoRenew) {
        return false;
    }
    
    auto planIt = plans.find(it->second.planId);
    if (planIt == plans.end()) {
        return false;
    }
    
    // Process payment
    std::cout << "Processing renewal for subscription: " << subscriptionId 
              << " ($" << planIt->second.price << ")" << std::endl;
    
    // Update next billing date
    it->second.nextBillingDate += 2592000; // Add 30 days
    
    return true;
}

std::vector<Subscription> SubscriptionManager::getUserSubscriptions(const std::string& userId) const {
    std::vector<Subscription> userSubs;
    
    for (const auto& [id, sub] : subscriptions) {
        if (sub.userId == userId) {
            userSubs.push_back(sub);
        }
    }
    
    return userSubs;
}

std::vector<SubscriptionPlan> SubscriptionManager::getAvailablePlans() const {
    std::vector<SubscriptionPlan> availablePlans;
    
    for (const auto& [id, plan] : plans) {
        availablePlans.push_back(plan);
    }
    
    return availablePlans;
}

SubscriptionManager::SubscriptionStats SubscriptionManager::getStatistics() const {
    SubscriptionStats stats;
    stats.totalSubscriptions = subscriptions.size();
    stats.activeSubscriptions = 0;
    stats.monthlyRevenue = 0.0;
    stats.churnRate = 0.0;
    
    int cancelledCount = 0;
    
    for (const auto& [id, sub] : subscriptions) {
        if (sub.status == "active") {
            stats.activeSubscriptions++;
            
            auto planIt = plans.find(sub.planId);
            if (planIt != plans.end()) {
                stats.monthlyRevenue += planIt->second.price;
                stats.subscriptionsByPlan[sub.planId]++;
            }
        } else if (sub.status == "cancelled") {
            cancelledCount++;
        }
    }
    
    if (stats.totalSubscriptions > 0) {
        stats.churnRate = (static_cast<double>(cancelledCount) / stats.totalSubscriptions) * 100.0;
    }
    
    return stats;
}

std::string SubscriptionManager::generateSubscriptionId() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(100000000, 999999999);
    
    std::stringstream ss;
    ss << "SUB_" << dis(gen);
    return ss.str();
}

} // namespace VirtualMoney

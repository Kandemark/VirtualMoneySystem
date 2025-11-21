#include "SubscriptionManager.h"

bool SubscriptionManager::subscribe(const std::string& userId, SubscriptionPlan plan) {
    Subscription sub;
    sub.userId = userId;
    sub.plan = plan;
    sub.startDate = std::chrono::system_clock::now();
    sub.endDate = sub.startDate + std::chrono::hours(24 * 30);
    sub.isActive = true;
    sub.monthlyPrice = getSubscriptionPrice(plan);
    subscriptions[userId] = sub;
    return true;
}

bool SubscriptionManager::cancelSubscription(const std::string& userId) {
    auto it = subscriptions.find(userId);
    if (it != subscriptions.end()) {
        it->second.isActive = false;
        return true;
    }
    return false;
}

Subscription SubscriptionManager::getSubscription(const std::string& userId) {
    return subscriptions.at(userId);
}

bool SubscriptionManager::isSubscriptionActive(const std::string& userId) {
    auto it = subscriptions.find(userId);
    if (it != subscriptions.end()) {
        return it->second.isActive && std::chrono::system_clock::now() < it->second.endDate;
    }
    return false;
}

double SubscriptionManager::getSubscriptionPrice(SubscriptionPlan plan) {
    switch (plan) {
        case SubscriptionPlan::FREE: return 0.0;
        case SubscriptionPlan::BASIC: return 9.99;
        case SubscriptionPlan::PREMIUM: return 29.99;
        case SubscriptionPlan::ENTERPRISE: return 99.99;
    }
    return 0.0;
}

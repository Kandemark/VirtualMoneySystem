#ifndef SUBSCRIPTION_MANAGER_H
#define SUBSCRIPTION_MANAGER_H
#include <string>
#include <map>
#include <chrono>

enum class SubscriptionPlan { FREE, BASIC, PREMIUM, ENTERPRISE };

struct Subscription {
    std::string userId;
    SubscriptionPlan plan;
    std::chrono::system_clock::time_point startDate;
    std::chrono::system_clock::time_point endDate;
    bool isActive;
    double monthlyPrice;
};

class SubscriptionManager {
public:
    bool subscribe(const std::string& userId, SubscriptionPlan plan);
    bool cancelSubscription(const std::string& userId);
    Subscription getSubscription(const std::string& userId);
    bool isSubscriptionActive(const std::string& userId);
    double getSubscriptionPrice(SubscriptionPlan plan);
private:
    std::map<std::string, Subscription> subscriptions;
};

#endif

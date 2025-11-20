#include "BehaviorMonitor.h"
#include <chrono>
#include <iomanip>
#include <sstream>

void BehaviorMonitor::recordEvent(const std::string& userId, const std::string& action) {
    BehaviorEvent event;
    event.userId = userId;
    event.action = action;
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
    event.timestamp = oss.str();
    behaviorHistory[userId].push_back(event);
}

bool BehaviorMonitor::detectAnomalousActivity(const std::string& userId) {
    auto it = behaviorHistory.find(userId);
    if (it == behaviorHistory.end()) return false;
    
    if (it->second.size() > 100) {
        return true;
    }
    return false;
}

std::vector<BehaviorEvent> BehaviorMonitor::getUserBehaviorHistory(const std::string& userId) {
    auto it = behaviorHistory.find(userId);
    return (it != behaviorHistory.end()) ? it->second : std::vector<BehaviorEvent>{};
}

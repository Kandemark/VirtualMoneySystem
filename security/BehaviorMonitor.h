#ifndef BEHAVIOR_MONITOR_H
#define BEHAVIOR_MONITOR_H
#include <string>
#include <vector>
#include <map>

struct BehaviorEvent {
    std::string userId;
    std::string action;
    std::string timestamp;
};

class BehaviorMonitor {
public:
    void recordEvent(const std::string& userId, const std::string& action);
    bool detectAnomalousActivity(const std::string& userId);
    std::vector<BehaviorEvent> getUserBehaviorHistory(const std::string& userId);
private:
    std::map<std::string, std::vector<BehaviorEvent>> behaviorHistory;
};

#endif

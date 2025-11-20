#ifndef ALERT_POLICY_H
#define ALERT_POLICY_H
#include <string>

class AlertPolicy {
public:
    bool shouldAlert(const std::string& eventType, double threshold) const;
    void setThreshold(const std::string& eventType, double threshold);
};

#endif

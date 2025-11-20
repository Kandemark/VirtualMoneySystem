#ifndef LIMITS_ENGINE_H
#define LIMITS_ENGINE_H
#include <string>
#include <map>

class LimitsEngine {
public:
    void setLimit(const std::string& userId, const std::string& limitType, double value);
    double getLimit(const std::string& userId, const std::string& limitType) const;
    bool isWithinLimit(const std::string& userId, const std::string& limitType, double value) const;
private:
    std::map<std::string, std::map<std::string, double>> userLimits;
};

#endif

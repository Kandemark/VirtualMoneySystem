#include "LimitsEngine.h"

void LimitsEngine::setLimit(const std::string& userId, const std::string& limitType, double value) {
    userLimits[userId][limitType] = value;
}

double LimitsEngine::getLimit(const std::string& userId, const std::string& limitType) const {
    auto userIt = userLimits.find(userId);
    if (userIt != userLimits.end()) {
        auto limitIt = userIt->second.find(limitType);
        if (limitIt != userIt->second.end()) {
            return limitIt->second;
        }
    }
    return 10000.0;
}

bool LimitsEngine::isWithinLimit(const std::string& userId, const std::string& limitType, double value) const {
    return value <= getLimit(userId, limitType);
}

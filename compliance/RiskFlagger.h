/**
 * @file RiskFlagger.h
 * @brief Risk flagging system
 */

#ifndef RISK_FLAGGER_H
#define RISK_FLAGGER_H

#include <string>

class RiskFlagger {
public:
    void flagRisk(const std::string& userId, const std::string& riskType, int severity);
    std::string getRiskLevel(const std::string& userId);
    void clearFlag(const std::string& userId, const std::string& riskType);
};

#endif

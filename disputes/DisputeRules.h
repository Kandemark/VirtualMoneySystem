/**
 * @file DisputeRules.h
 * @brief Dispute resolution rules
 */

#ifndef DISPUTE_RULES_H
#define DISPUTE_RULES_H

#include <string>

class DisputeRules {
public:
    void addRule(const std::string& ruleId, const std::string& condition, const std::string& action);
    bool evaluateRule(const std::string& ruleId, const std::string& disputeData);
    std::string getRecommendedAction(const std::string& disputeId);
};

#endif

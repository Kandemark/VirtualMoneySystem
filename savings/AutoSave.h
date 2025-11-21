/**
 * @file AutoSave.h
 * @brief Automatic savings features
 */

#ifndef AUTO_SAVE_H
#define AUTO_SAVE_H

#include <string>
#include <map>

/**
 * @brief Auto-save rule
 */
struct AutoSaveRule {
    std::string ruleId;
    std::string userId;
    std::string type;  // round_up, percentage, fixed
    double amount;
    bool isActive;
};

/**
 * @brief Manages automatic savings
 */
class AutoSave {
public:
    /**
     * @brief Create auto-save rule
     * @param userId User identifier
     * @param type Rule type
     * @param amount Amount or percentage
     * @return Rule ID
     */
    std::string createRule(const std::string& userId, const std::string& type, double amount);
    
    /**
     * @brief Process transaction for auto-save
     * @param userId User identifier
     * @param transactionAmount Transaction amount
     * @return Amount saved
     */
    double processTransaction(const std::string& userId, double transactionAmount);
    
    /**
     * @brief Enable/disable rule
     * @param ruleId Rule identifier
     * @param enabled true to enable
     */
    void setRuleStatus(const std::string& ruleId, bool enabled);

private:
    std::map<std::string, AutoSaveRule> rules;
};

#endif

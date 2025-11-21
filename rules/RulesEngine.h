/**
 * @file RulesEngine.h
 * @brief Business rules engine for policy enforcement
 */

#ifndef RULES_ENGINE_H
#define RULES_ENGINE_H

#include <string>
#include <map>
#include <vector>

/**
 * @brief Evaluates and enforces business rules
 */
class RulesEngine {
public:
    /**
     * @brief Evaluate a rule
     * @param ruleId Rule identifier
     * @param context Evaluation context data
     * @return true if rule passes
     */
    bool evaluateRule(const std::string& ruleId, const std::map<std::string, std::string>& context);
    
    /**
     * @brief Load rules from configuration
     * @param configPath Path to rules configuration
     */
    void loadRules(const std::string& configPath);
    
    /**
     * @brief Add custom rule
     * @param ruleId Rule identifier
     * @param ruleDefinition Rule definition
     */
    void addRule(const std::string& ruleId, const std::string& ruleDefinition);
    
    /**
     * @brief Get all active rules
     * @return Vector of rule IDs
     */
    std::vector<std::string> getActiveRules();

private:
    std::map<std::string, std::string> rules;
};

#endif

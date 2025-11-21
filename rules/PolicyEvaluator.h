/**
 * @file PolicyEvaluator.h
 * @brief Evaluate complex business policies
 */

#ifndef POLICY_EVALUATOR_H
#define POLICY_EVALUATOR_H

#include <string>
#include <map>

/**
 * @brief Evaluates business policies
 */
class PolicyEvaluator {
public:
    /**
     * @brief Evaluate policy
     * @param policyId Policy identifier
     * @param data Policy evaluation data
     * @return true if policy is satisfied
     */
    bool evaluatePolicy(const std::string& policyId, const std::map<std::string, std::string>& data);
    
    /**
     * @brief Register policy
     * @param policyId Policy identifier
     * @param policyExpression Policy expression
     */
    void registerPolicy(const std::string& policyId, const std::string& policyExpression);

private:
    std::map<std::string, std::string> policies;
};

#endif

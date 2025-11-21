/**
 * @file PlanCatalog.h
 * @brief Manages subscription plan definitions and pricing
 * 
 * The PlanCatalog maintains a catalog of available subscription plans,
 * their features, pricing, and billing cycles.
 */

#ifndef PLAN_CATALOG_H
#define PLAN_CATALOG_H

#include <string>
#include <map>
#include <vector>

/**
 * @brief Represents a subscription plan
 */
struct Plan {
    std::string planId;           ///< Unique plan identifier
    std::string name;             ///< Plan display name
    double monthlyPrice;          ///< Monthly subscription price
    double annualPrice;           ///< Annual subscription price (discounted)
    std::vector<std::string> features;  ///< List of included features
    int maxUsers;                 ///< Maximum number of users allowed
    int maxTransactions;          ///< Maximum monthly transactions
};

/**
 * @brief Manages the catalog of subscription plans
 */
class PlanCatalog {
public:
    /**
     * @brief Add a new plan to the catalog
     * @param plan The plan to add
     */
    void addPlan(const Plan& plan);
    
    /**
     * @brief Get a plan by its ID
     * @param planId The unique plan identifier
     * @return The plan details
     */
    Plan getPlan(const std::string& planId);
    
    /**
     * @brief Get all available plans
     * @return Vector of all plans
     */
    std::vector<Plan> getAllPlans();
    
    /**
     * @brief Check if a feature is included in a plan
     * @param planId The plan identifier
     * @param feature The feature name
     * @return true if feature is included, false otherwise
     */
    bool hasFeature(const std::string& planId, const std::string& feature);

private:
    /// Map of plan IDs to plan details
    std::map<std::string, Plan> plans;
};

#endif // PLAN_CATALOG_H

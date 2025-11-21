/**
 * @file BillingEngine.h
 * @brief Handles recurring billing and invoice generation for subscriptions
 * 
 * The BillingEngine manages automated billing cycles, invoice generation,
 * and payment collection for subscription-based services.
 */

#ifndef BILLING_ENGINE_H
#define BILLING_ENGINE_H

#include <string>
#include <map>
#include <chrono>

/**
 * @brief Manages subscription billing and invoice generation
 * 
 * This class handles the automated billing process for subscriptions,
 * including invoice generation, payment processing, and billing cycle management.
 */
class BillingEngine {
public:
    /**
     * @brief Process billing for a specific user
     * @param userId The unique identifier of the user
     * @return true if billing was successful, false otherwise
     */
    bool processBilling(const std::string& userId);
    
    /**
     * @brief Generate an invoice for a user's subscription
     * @param userId The unique identifier of the user
     * @param amount The billing amount
     * @return The generated invoice ID
     */
    std::string generateInvoice(const std::string& userId, double amount);
    
    /**
     * @brief Retrieve the next billing date for a user
     * @param userId The unique identifier of the user
     * @return The next billing date as a time_point
     */
    std::chrono::system_clock::time_point getNextBillingDate(const std::string& userId);
    
    /**
     * @brief Check if a user has any failed payments
     * @param userId The unique identifier of the user
     * @return true if there are failed payments, false otherwise
     */
    bool hasFailedPayments(const std::string& userId);

private:
    /// Map of user IDs to their next billing dates
    std::map<std::string, std::chrono::system_clock::time_point> billingSchedule;
    
    /// Map of user IDs to failed payment counts
    std::map<std::string, int> failedPayments;
};

#endif // BILLING_ENGINE_H

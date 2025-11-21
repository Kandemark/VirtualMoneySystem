/**
 * @file SDKClient.h
 * @brief Client SDK for platform integration
 */

#ifndef SDK_CLIENT_H
#define SDK_CLIENT_H

#include <string>

/**
 * @brief Main SDK client for developers
 */
class SDKClient {
public:
    /**
     * @brief Initialize SDK with API key
     * @param apiKey API authentication key
     * @param environment Environment (production/sandbox)
     */
    SDKClient(const std::string& apiKey, const std::string& environment = "production");
    
    /**
     * @brief Create a transaction
     * @param fromUserId Source user
     * @param toUserId Destination user
     * @param amount Transaction amount
     * @return Transaction ID
     */
    std::string createTransaction(const std::string& fromUserId, const std::string& toUserId, double amount);
    
    /**
     * @brief Get user balance
     * @param userId User identifier
     * @return Current balance
     */
    double getBalance(const std::string& userId);
    
    /**
     * @brief Verify webhook signature
     * @param payload Webhook payload
     * @param signature Provided signature
     * @return true if signature is valid
     */
    bool verifyWebhook(const std::string& payload, const std::string& signature);

private:
    std::string apiKey;
    std::string environment;
};

#endif

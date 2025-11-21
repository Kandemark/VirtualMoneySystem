/**
 * @file SDKExamples.h
 * @brief Code examples for SDK usage
 */

#ifndef SDK_EXAMPLES_H
#define SDK_EXAMPLES_H

#include <string>

/**
 * @brief Provides example code for common SDK operations
 */
class SDKExamples {
public:
    /**
     * @brief Get example code for creating a transaction
     * @return Example code string
     */
    static std::string getTransactionExample();
    
    /**
     * @brief Get example code for handling webhooks
     * @return Example code string
     */
    static std::string getWebhookExample();
    
    /**
     * @brief Get example code for user management
     * @return Example code string
     */
    static std::string getUserManagementExample();
};

#endif

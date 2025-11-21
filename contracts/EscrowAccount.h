/**
 * @file EscrowAccount.h
 * @brief Escrow account management
 */

#ifndef ESCROW_ACCOUNT_H
#define ESCROW_ACCOUNT_H

#include <string>

/**
 * @brief Manages escrow accounts for secure transactions
 */
class EscrowAccount {
public:
    /**
     * @brief Create escrow account
     * @param buyerId Buyer identifier
     * @param sellerId Seller identifier
     * @param amount Escrow amount
     * @return Escrow ID
     */
    std::string createEscrow(const std::string& buyerId, const std::string& sellerId, double amount);
    
    /**
     * @brief Release funds to seller
     * @param escrowId Escrow identifier
     * @return true if released
     */
    bool releaseFunds(const std::string& escrowId);
    
    /**
     * @brief Refund to buyer
     * @param escrowId Escrow identifier
     * @return true if refunded
     */
    bool refundBuyer(const std::string& escrowId);
    
    /**
     * @brief Get escrow status
     * @param escrowId Escrow identifier
     * @return Status string
     */
    std::string getStatus(const std::string& escrowId);
};

#endif

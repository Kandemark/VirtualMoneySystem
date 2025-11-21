/**
 * @file DisputeManager.h
 * @brief Transaction dispute management
 */

#ifndef DISPUTE_MANAGER_H
#define DISPUTE_MANAGER_H

#include <string>
#include <map>

/**
 * @brief Status of a dispute
 */
enum class DisputeStatus {
    OPEN,           ///< Dispute is open
    INVESTIGATING,  ///< Under investigation
    RESOLVED,       ///< Resolved in favor of one party
    CLOSED          ///< Dispute closed
};

/**
 * @brief Represents a transaction dispute
 */
struct Dispute {
    std::string disputeId;
    std::string transactionId;
    std::string userId;
    std::string reason;
    DisputeStatus status;
    std::string resolution;
};

/**
 * @brief Manages transaction disputes
 */
class DisputeManager {
public:
    /**
     * @brief File a new dispute
     * @param transactionId Transaction being disputed
     * @param userId User filing dispute
     * @param reason Reason for dispute
     * @return Dispute ID
     */
    std::string fileDispute(const std::string& transactionId, const std::string& userId, const std::string& reason);
    
    /**
     * @brief Update dispute status
     * @param disputeId Dispute identifier
     * @param status New status
     */
    void updateStatus(const std::string& disputeId, DisputeStatus status);
    
    /**
     * @brief Resolve dispute
     * @param disputeId Dispute identifier
     * @param resolution Resolution details
     */
    void resolveDispute(const std::string& disputeId, const std::string& resolution);
    
    /**
     * @brief Get dispute details
     * @param disputeId Dispute identifier
     * @return Dispute information
     */
    Dispute getDispute(const std::string& disputeId);

private:
    std::map<std::string, Dispute> disputes;
};

#endif

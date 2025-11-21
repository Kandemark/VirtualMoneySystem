/**
 * @file ClaimProcessor.h
 * @brief Process insurance claims
 */

#ifndef CLAIM_PROCESSOR_H
#define CLAIM_PROCESSOR_H

#include <string>
#include <map>

/**
 * @brief Insurance claim status
 */
enum class ClaimStatus {
    PENDING,
    APPROVED,
    REJECTED,
    PAID
};

/**
 * @brief Insurance claim
 */
struct Claim {
    std::string claimId;
    std::string policyId;
    double amount;
    std::string reason;
    ClaimStatus status;
};

/**
 * @brief Processes insurance claims
 */
class ClaimProcessor {
public:
    /**
     * @brief Process a claim
     * @param claimId Claim identifier
     * @return true if processed successfully
     */
    bool processClaim(const std::string& claimId);
    
    /**
     * @brief Approve claim
     * @param claimId Claim identifier
     * @param approvedAmount Approved payout amount
     */
    void approveClaim(const std::string& claimId, double approvedAmount);
    
    /**
     * @brief Reject claim
     * @param claimId Claim identifier
     * @param reason Rejection reason
     */
    void rejectClaim(const std::string& claimId, const std::string& reason);
    
    /**
     * @brief Get claim status
     * @param claimId Claim identifier
     * @return Claim status
     */
    ClaimStatus getClaimStatus(const std::string& claimId);

private:
    std::map<std::string, Claim> claims;
};

#endif

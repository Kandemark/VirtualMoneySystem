/**
 * @file ZKProof.h
 * @brief Zero-knowledge proof system for privacy-preserving authentication
 */

#ifndef ZK_PROOF_H
#define ZK_PROOF_H

#include <string>
#include <vector>
#include <cstdint>
#include <array>

namespace VirtualMoney {

/**
 * @brief Zero-knowledge proof
 */
struct ZeroKnowledgeProof {
    std::vector<uint8_t> commitment;
    std::vector<uint8_t> challenge;
    std::vector<uint8_t> response;
    std::string proofType; // "balance", "identity", "age", "compliance"
};

/**
 * @brief Zero-knowledge proof system
 * 
 * Features:
 * - Prove statements without revealing data
 * - Privacy-preserving authentication
 * - Selective disclosure to authorities
 * - zk-SNARKs for succinct proofs
 * - Regulatory compliance with privacy
 */
class ZKProof {
public:
    ZKProof();
    
    /**
     * @brief Prove balance exceeds threshold without revealing amount
     * @param actualBalance User's actual balance
     * @param threshold Minimum required balance
     * @return Zero-knowledge proof
     */
    ZeroKnowledgeProof proveBalanceAbove(double actualBalance, double threshold);
    
    /**
     * @brief Verify balance proof
     * @param proof Zero-knowledge proof
     * @param threshold Claimed threshold
     * @return true if proof is valid
     */
    bool verifyBalanceProof(const ZeroKnowledgeProof& proof, double threshold);
    
    /**
     * @brief Prove age without revealing birthdate
     * @param birthYear Actual birth year
     * @param minimumAge Required minimum age
     * @return Zero-knowledge proof
     */
    ZeroKnowledgeProof proveAgeAbove(int birthYear, int minimumAge);
    
    /**
     * @brief Prove not on sanctions list without revealing identity
     * @param userId User identifier
     * @param sanctionsList List of sanctioned entities
     * @return Zero-knowledge proof
     */
    ZeroKnowledgeProof proveNotSanctioned(const std::string& userId,
                                         const std::vector<std::string>& sanctionsList);
    
    /**
     * @brief Prove compliance without revealing transaction details
     * @param transactionData Encrypted transaction data
     * @param complianceRules Rules to prove compliance with
     * @return Zero-knowledge proof
     */
    ZeroKnowledgeProof proveCompliance(const std::vector<uint8_t>& transactionData,
                                       const std::vector<std::string>& complianceRules);
    
    /**
     * @brief Generate commitment (first step of ZK proof)
     * @param secret Secret value
     * @param randomness Random blinding factor
     * @return Commitment
     */
    std::vector<uint8_t> generateCommitment(const std::vector<uint8_t>& secret,
                                            const std::vector<uint8_t>& randomness);
    
    /**
     * @brief Selective disclosure to authorities
     * @param proof Zero-knowledge proof
     * @param authorityPublicKey Authority's public key
     * @return Encrypted disclosure for authority only
     */
    std::vector<uint8_t> selectiveDisclosure(const ZeroKnowledgeProof& proof,
                                             const std::vector<uint8_t>& authorityPublicKey);

private:
    std::array<uint8_t, 32> systemSecret;
    
    std::vector<uint8_t> hash(const std::vector<uint8_t>& data);
    std::vector<uint8_t> generateRandomness(size_t length);
    bool verifyCommitment(const std::vector<uint8_t>& commitment,
                         const std::vector<uint8_t>& secret,
                         const std::vector<uint8_t>& randomness);
};

} // namespace VirtualMoney

#endif // ZK_PROOF_H

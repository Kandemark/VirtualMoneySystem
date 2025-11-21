/**
 * @file SelfAuditChain.h
 * @brief Immutable self-auditing blockchain ledger
 */

#ifndef SELF_AUDIT_CHAIN_H
#define SELF_AUDIT_CHAIN_H

#include <string>
#include <vector>
#include <ctime>
#include <memory>

namespace VirtualMoney {

/**
 * @brief Block in the audit chain
 */
struct AuditBlock {
    uint64_t index;
    std::time_t timestamp;
    std::string previousHash;
    std::string merkleRoot;
    std::vector<std::string> transactions;
    uint64_t nonce;
    std::string blockHash;
    
    std::string calculateHash() const;
    std::string calculateMerkleRoot() const;
};

/**
 * @brief Self-auditing blockchain for immutable transaction records
 * 
 * Features:
 * - Cryptographically sealed blocks
 * - Merkle tree for efficient verification
 * - Self-verification capability
 * - Tamper-proof audit trail
 * - RFC 3161 timestamp integration
 */
class SelfAuditChain {
public:
    SelfAuditChain();
    
    /**
     * @brief Add transaction to pending pool
     */
    void addTransaction(const std::string& txData);
    
    /**
     * @brief Mine new block with pending transactions
     * @param difficulty Mining difficulty (proof-of-work)
     */
    void mineBlock(int difficulty = 4);
    
    /**
     * @brief Verify entire chain integrity
     * @return true if chain is valid
     */
    bool verifyChain() const;
    
    /**
     * @brief Verify specific transaction exists
     * @param txHash Transaction hash
     * @return Merkle proof path
     */
    std::vector<std::string> getMerkleProof(const std::string& txHash) const;
    
    /**
     * @brief Get block by index
     */
    const AuditBlock* getBlock(uint64_t index) const;
    
    /**
     * @brief Get chain length
     */
    size_t getChainLength() const { return chain.size(); }
    
    /**
     * @brief Export chain for external audit
     * @return JSON representation of entire chain
     */
    std::string exportForAudit() const;
    
    /**
     * @brief Get chain statistics
     */
    struct ChainStats {
        uint64_t totalBlocks;
        uint64_t totalTransactions;
        std::time_t firstBlock;
        std::time_t lastBlock;
        double averageBlockTime;
    };
    ChainStats getStatistics() const;

private:
    std::vector<AuditBlock> chain;
    std::vector<std::string> pendingTransactions;
    
    AuditBlock createGenesisBlock();
    AuditBlock mineNewBlock(const std::vector<std::string>& transactions);
    bool isValidBlock(const AuditBlock& block, const AuditBlock& previousBlock) const;
    std::string hashSHA256(const std::string& data) const;
};

} // namespace VirtualMoney

#endif // SELF_AUDIT_CHAIN_H

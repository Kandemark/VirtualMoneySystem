/**
 * @file HashChain.h
 * @brief Blockchain-style hash chain for audit logs
 */

#ifndef HASH_CHAIN_H
#define HASH_CHAIN_H

#include <string>
#include <vector>

/**
 * @brief Hash chain entry
 */
struct ChainEntry {
    std::string hash;
    std::string previousHash;
    std::string data;
    std::string timestamp;
};

/**
 * @brief Implements hash chain for tamper-proof logging
 */
class HashChain {
public:
    /**
     * @brief Add entry to chain
     * @param data Entry data
     * @return Entry hash
     */
    std::string addEntry(const std::string& data);
    
    /**
     * @brief Verify chain integrity
     * @return true if chain is valid
     */
    bool verifyChain();
    
    /**
     * @brief Get chain length
     * @return Number of entries
     */
    size_t getChainLength();
    
    /**
     * @brief Get entry by index
     * @param index Entry index
     * @return Chain entry
     */
    ChainEntry getEntry(size_t index);

private:
    std::vector<ChainEntry> chain;
    std::string calculateHash(const std::string& data, const std::string& previousHash);
};

#endif

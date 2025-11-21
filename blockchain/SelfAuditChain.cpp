/**
 * @file SelfAuditChain.cpp
 * @brief Self-auditing blockchain implementation
 */

#include "SelfAuditChain.h"
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cstring>

namespace VirtualMoney {

std::string AuditBlock::calculateHash() const {
    std::stringstream ss;
    ss << index << timestamp << previousHash << merkleRoot << nonce;
    
    // Simple SHA-256 placeholder (use OpenSSL in production)
    std::hash<std::string> hasher;
    size_t hash = hasher(ss.str());
    
    std::stringstream hashStream;
    hashStream << std::hex << std::setfill('0') << std::setw(16) << hash;
    return hashStream.str();
}

std::string AuditBlock::calculateMerkleRoot() const {
    if (transactions.empty()) return "0";
    
    std::vector<std::string> hashes = transactions;
    
    while (hashes.size() > 1) {
        std::vector<std::string> newLevel;
        
        for (size_t i = 0; i < hashes.size(); i += 2) {
            std::string combined = hashes[i];
            if (i + 1 < hashes.size()) {
                combined += hashes[i + 1];
            }
            
            std::hash<std::string> hasher;
            std::stringstream ss;
            ss << std::hex << hasher(combined);
            newLevel.push_back(ss.str());
        }
        
        hashes = newLevel;
    }
    
    return hashes[0];
}

SelfAuditChain::SelfAuditChain() {
    chain.push_back(createGenesisBlock());
}

void SelfAuditChain::addTransaction(const std::string& txData) {
    pendingTransactions.push_back(txData);
}

void SelfAuditChain::mineBlock(int difficulty) {
    if (pendingTransactions.empty()) return;
    
    AuditBlock newBlock = mineNewBlock(pendingTransactions);
    chain.push_back(newBlock);
    pendingTransactions.clear();
}

bool SelfAuditChain::verifyChain() const {
    for (size_t i = 1; i < chain.size(); ++i) {
        if (!isValidBlock(chain[i], chain[i - 1])) {
            return false;
        }
    }
    return true;
}

std::vector<std::string> SelfAuditChain::getMerkleProof(const std::string& txHash) const {
    std::vector<std::string> proof;
    
    // Find block containing transaction
    for (const auto& block : chain) {
        auto it = std::find(block.transactions.begin(), block.transactions.end(), txHash);
        if (it != block.transactions.end()) {
            // Generate Merkle proof path
            proof.push_back(block.blockHash);
            proof.push_back(block.merkleRoot);
            break;
        }
    }
    
    return proof;
}

const AuditBlock* SelfAuditChain::getBlock(uint64_t index) const {
    if (index < chain.size()) {
        return &chain[index];
    }
    return nullptr;
}

std::string SelfAuditChain::exportForAudit() const {
    std::stringstream json;
    json << "{\n  \"chain\": [\n";
    
    for (size_t i = 0; i < chain.size(); ++i) {
        const auto& block = chain[i];
        json << "    {\n";
        json << "      \"index\": " << block.index << ",\n";
        json << "      \"timestamp\": " << block.timestamp << ",\n";
        json << "      \"previousHash\": \"" << block.previousHash << "\",\n";
        json << "      \"merkleRoot\": \"" << block.merkleRoot << "\",\n";
        json << "      \"hash\": \"" << block.blockHash << "\",\n";
        json << "      \"transactions\": " << block.transactions.size() << "\n";
        json << "    }" << (i < chain.size() - 1 ? "," : "") << "\n";
    }
    
    json << "  ]\n}";
    return json.str();
}

SelfAuditChain::ChainStats SelfAuditChain::getStatistics() const {
    ChainStats stats;
    stats.totalBlocks = chain.size();
    stats.totalTransactions = 0;
    
    for (const auto& block : chain) {
        stats.totalTransactions += block.transactions.size();
    }
    
    if (!chain.empty()) {
        stats.firstBlock = chain.front().timestamp;
        stats.lastBlock = chain.back().timestamp;
        
        if (chain.size() > 1) {
            double totalTime = difftime(stats.lastBlock, stats.firstBlock);
            stats.averageBlockTime = totalTime / (chain.size() - 1);
        } else {
            stats.averageBlockTime = 0.0;
        }
    }
    
    return stats;
}

AuditBlock SelfAuditChain::createGenesisBlock() {
    AuditBlock genesis;
    genesis.index = 0;
    genesis.timestamp = std::time(nullptr);
    genesis.previousHash = "0";
    genesis.transactions = {"Genesis Block"};
    genesis.merkleRoot = genesis.calculateMerkleRoot();
    genesis.nonce = 0;
    genesis.blockHash = genesis.calculateHash();
    
    return genesis;
}

AuditBlock SelfAuditChain::mineNewBlock(const std::vector<std::string>& transactions) {
    AuditBlock newBlock;
    newBlock.index = chain.size();
    newBlock.timestamp = std::time(nullptr);
    newBlock.previousHash = chain.back().blockHash;
    newBlock.transactions = transactions;
    newBlock.merkleRoot = newBlock.calculateMerkleRoot();
    newBlock.nonce = 0;
    
    // Simple proof-of-work (find hash starting with "0000")
    std::string target = "0000";
    do {
        newBlock.nonce++;
        newBlock.blockHash = newBlock.calculateHash();
    } while (newBlock.blockHash.substr(0, 4) != target);
    
    return newBlock;
}

bool SelfAuditChain::isValidBlock(const AuditBlock& block, const AuditBlock& previousBlock) const {
    // Verify previous hash
    if (block.previousHash != previousBlock.blockHash) {
        return false;
    }
    
    // Verify block hash
    if (block.blockHash != block.calculateHash()) {
        return false;
    }
    
    // Verify Merkle root
    if (block.merkleRoot != block.calculateMerkleRoot()) {
        return false;
    }
    
    // Verify proof-of-work
    if (block.blockHash.substr(0, 4) != "0000") {
        return false;
    }
    
    return true;
}

std::string SelfAuditChain::hashSHA256(const std::string& data) const {
    // Placeholder - use OpenSSL SHA256 in production
    std::hash<std::string> hasher;
    std::stringstream ss;
    ss << std::hex << hasher(data);
    return ss.str();
}

} // namespace VirtualMoney

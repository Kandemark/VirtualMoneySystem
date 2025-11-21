/**
 * @file MultiChainBridge.h
 * @brief Multi-chain blockchain bridge for cross-chain operations
 */

#ifndef MULTI_CHAIN_BRIDGE_H
#define MULTI_CHAIN_BRIDGE_H

#include <string>
#include <vector>
#include <map>

namespace VirtualMoney {
namespace Blockchain {

enum class Chain {
    ETHEREUM,
    POLYGON,
    SOLANA,
    AVALANCHE,
    BINANCE_SMART_CHAIN,
    ARBITRUM,
    OPTIMISM,
    FANTOM
};

struct ChainInfo {
    Chain chain;
    std::string name;
    std::string rpcUrl;
    int chainId;
    std::string nativeCurrency;
    double gasPrice;
    bool active;
};

struct CrossChainSwap {
    std::string swapId;
    Chain fromChain;
    Chain toChain;
    std::string fromToken;
    std::string toToken;
    double amount;
    std::string status; // "pending", "completed", "failed"
    std::time_t timestamp;
};

class MultiChainBridge {
public:
    MultiChainBridge();
    
    /**
     * @brief Initialize bridge for chain
     */
    bool initializeChain(Chain chain);
    
    /**
     * @brief Cross-chain atomic swap
     */
    std::string createAtomicSwap(Chain fromChain, Chain toChain, 
                                 const std::string& fromToken, 
                                 const std::string& toToken, 
                                 double amount);
    
    /**
     * @brief Bridge assets between chains
     */
    bool bridgeAsset(Chain fromChain, Chain toChain, 
                    const std::string& asset, double amount);
    
    /**
     * @brief Get balance on chain
     */
    double getBalanceOnChain(Chain chain, const std::string& address);
    
    /**
     * @brief Deploy contract on chain
     */
    std::string deployContract(Chain chain, const std::string& bytecode);
    
    /**
     * @brief Call contract function
     */
    std::string callContract(Chain chain, const std::string& contractAddress, 
                            const std::string& function, 
                            const std::vector<std::string>& params);
    
    /**
     * @brief Get supported chains
     */
    std::vector<ChainInfo> getSupportedChains();
    
    /**
     * @brief Estimate bridge fee
     */
    double estimateBridgeFee(Chain fromChain, Chain toChain, double amount);
    
    /**
     * @brief Get swap status
     */
    CrossChainSwap getSwapStatus(const std::string& swapId);
    
    /**
     * @brief Add liquidity to bridge pool
     */
    bool addLiquidity(Chain chain, const std::string& token, double amount);
    
private:
    std::map<Chain, ChainInfo> chains;
    std::map<std::string, CrossChainSwap> swaps;
    
    std::string generateSwapId();
    bool verifyChainSupport(Chain chain);
};

} // namespace Blockchain
} // namespace VirtualMoney

#endif

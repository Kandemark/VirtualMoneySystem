#pragma once
#include <ctime>
#include <map>
#include <string>
#include <vector>


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
  std::string status;
  time_t timestamp;
};

class MultiChainBridge {
public:
  MultiChainBridge();

  bool initializeChain(Chain chain);
  std::string createAtomicSwap(Chain fromChain, Chain toChain,
                               const std::string &fromToken,
                               const std::string &toToken, double amount);
  bool bridgeAsset(Chain fromChain, Chain toChain, const std::string &asset,
                   double amount);
  double getBalanceOnChain(Chain chain, const std::string &address);
  std::vector<ChainInfo> getSupportedChains();
  double estimateBridgeFee(Chain fromChain, Chain toChain, double amount);
  CrossChainSwap getSwapStatus(const std::string &swapId);

private:
  std::map<Chain, ChainInfo> chains;
  std::map<std::string, CrossChainSwap> swaps;

  std::string generateSwapId();
  bool verifyChainSupport(Chain chain);
};

} // namespace Blockchain
} // namespace VirtualMoney

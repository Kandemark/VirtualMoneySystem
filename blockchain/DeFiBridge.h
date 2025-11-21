#ifndef DEFI_BRIDGE_H
#define DEFI_BRIDGE_H
#include <string>

class DeFiBridge {
public:
    bool connectToProtocol(const std::string& protocolName);
    double getPoolLiquidity(const std::string& poolId);
    bool executeSwap(const std::string& fromToken, const std::string& toToken, double amount);
    double getAPY(const std::string& poolId);
};

#endif

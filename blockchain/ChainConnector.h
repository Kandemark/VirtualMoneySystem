#ifndef CHAIN_CONNECTOR_H
#define CHAIN_CONNECTOR_H
#include <string>

class ChainConnector {
public:
    bool connectToChain(const std::string& chainId);
    std::string getBlockchainAddress(const std::string& userId);
    double getBalance(const std::string& address);
    bool sendTransaction(const std::string& from, const std::string& to, double amount);
};

#endif

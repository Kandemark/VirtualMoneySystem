#ifndef WALLET_SYNC_H
#define WALLET_SYNC_H
#include <string>
#include <vector>

struct BlockchainTransaction {
    std::string txHash;
    std::string from;
    std::string to;
    double amount;
    int timestamp;
};

class WalletSync {
public:
    bool syncWallet(const std::string& address);
    std::vector<BlockchainTransaction> getTransactions(const std::string& address);
    int getLastSyncedBlock(const std::string& address);
};

#endif

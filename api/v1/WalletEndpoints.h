/**
 * @file WalletEndpoints.h
 * @brief API v1 wallet endpoints
 */

#ifndef WALLET_ENDPOINTS_V1_H
#define WALLET_ENDPOINTS_V1_H

#include <string>

namespace api {
namespace v1 {

class WalletEndpoints {
public:
    void registerRoutes();
    std::string createWallet(const std::string& userId);
    std::string getBalance(const std::string& walletId);
};

}
}

#endif

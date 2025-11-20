#ifndef WALLET_ENDPOINTS_H
#define WALLET_ENDPOINTS_H

#include "../vendor/crow/crow.h"
#include "../database/DatabaseManager.h"
#include "../core/TransactionEngine.h"
#include "../compliance/KYCValidator.h"
#include "../compliance/AMLScanner.h"
#include "../analytics/TransactionStats.h"
#include <mutex>

class WalletEndpoints {
public:
    WalletEndpoints(DatabaseManager& db, TransactionEngine& te, std::mutex& dbMutex, TransactionStats& stats);
    void registerRoutes(crow::SimpleApp& app);

private:
    DatabaseManager& dbManager;
    TransactionEngine& transactionEngine;
    std::mutex& dbMutex;
    KYCValidator kycValidator;
    AMLScanner amlScanner;
    TransactionStats& transactionStats;
};

#endif // WALLET_ENDPOINTS_H

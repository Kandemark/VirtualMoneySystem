#ifndef WALLET_ENDPOINTS_H
#define WALLET_ENDPOINTS_H

#include "../analytics/FraudSignalDetector.h"
#include "../analytics/TransactionStats.h"
#include "../core/TransactionEngine.h"
#include "../database/DatabaseManager.h"
#include "../transactions/TransactionLimits.h"
#include <mutex>


class WalletEndpoints {
public:
  WalletEndpoints(DatabaseManager &db, TransactionEngine &engine,
                  std::mutex &mutex, TransactionStats &stats,
                  FraudSignalDetector &fraud, TransactionLimits &limits);

  void registerRoutes();
  DatabaseManager &getDatabase() { return dbManager; } // Expose for UserManager
  std::mutex &getMutex() { return dbMutex; }
  TransactionEngine &getTransactionEngine() { return transactionEngine; }
  FraudSignalDetector &getFraudDetector() { return fraudDetector; }
  TransactionLimits &getTransactionLimits() { return transactionLimits; }

private:
  DatabaseManager &dbManager;
  TransactionEngine &transactionEngine;
  std::mutex &dbMutex;
  TransactionStats &transactionStats;
  FraudSignalDetector &fraudDetector;
  TransactionLimits &transactionLimits;
};

#endif // WALLET_ENDPOINTS_H

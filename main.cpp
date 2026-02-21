#include "analytics/FraudSignalDetector.h"
#include "analytics/TransactionStats.h"
#include "api/RESTServer.h"
#include "api/WalletEndpoints.h"
#include "core/TransactionEngine.h"
#include "database/DatabaseManager.h"
#include "transactions/TransactionLimits.h"
#include <iostream>
#include <mutex>


int main() {
  std::cout << "\n========================================\n";
  std::cout << "  VirtualMoneySystem v1.0.2\n";
  std::cout << "  HTTP Server + Authentication\n";
  std::cout << "========================================\n\n";

  try {
    std::cout << "Initializing...\n";
    DatabaseManager db("vms.db");
    std::mutex mtx;
    TransactionEngine txEngine; // Default constructor
    TransactionStats stats(txEngine);
    FraudSignalDetector fraud(txEngine);
    TransactionLimits limits(1000000.0);

    WalletEndpoints endpoints(db, txEngine, mtx, stats, fraud, limits);
    RESTServer server(endpoints);

    std::cout << "\nStarting on http://localhost:12345\n\n";
    server.run(12345);

  } catch (const std::exception &e) {
    std::cerr << "ERROR: " << e.what() << "\n";
    return 1;
  }

  return 0;
}
#include "core/Wallet.h"
#include "core/TransactionEngine.h"
#include "database/DatabaseManager.h"
#include "scheduler/JobScheduler.h"
#include "scheduler/RecurringPayments.h"
#include "api/RESTServer.h"
#include "api/WalletEndpoints.h"
#include "analytics/TransactionStats.h"
#include "analytics/FraudSignalDetector.h"
#include "transactions/TransactionLimits.h"
#include <iostream>
#include <memory>
#include <mutex>
#include <cstdlib>
#include <ctime>

// Use a single, global DatabaseManager instance for the entire application.
DatabaseManager dbManager("vms.db");
// A mutex to protect access to the shared DatabaseManager from multiple threads.
std::mutex dbMutex;

// The TransactionEngine will process transactions.
TransactionEngine transactionEngine;

int main()
{
    // Initialize the database once, before the server starts.
    try {
        dbManager.initialize();
    } catch (const std::runtime_error& e) {
        std::cerr << "Failed to initialize database: " << e.what() << std::endl;
        return 1;
    }

    // Initialize Scheduler
    JobScheduler scheduler;
    RecurringPayments recurringPayments(transactionEngine, dbManager);

    // Schedule recurring payment checks every 60 seconds
    scheduler.schedule([&recurringPayments]() {
        recurringPayments.processPayments();
    }, 60);

    scheduler.start();

    // Initialize Analytics
    TransactionStats transactionStats(transactionEngine);
    FraudSignalDetector fraudDetector(transactionEngine);

    // Initialize Limits
    TransactionLimits transactionLimits(50000.0); // Limit of 50,000 units

    // Initialize API
    WalletEndpoints walletEndpoints(dbManager, transactionEngine, dbMutex, transactionStats, fraudDetector, transactionLimits);
    RESTServer server(walletEndpoints);

    // Use a random port to avoid "Address already in use" errors in tests.
    srand(time(0));
    int port = 10000 + (rand() % 10000);
    
    server.run(port);
    
    // Stop scheduler on exit (though app.run() blocks)
    scheduler.stop();
}
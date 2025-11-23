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

// Global instances
DatabaseManager dbManager("vms.db");
std::mutex dbMutex;
TransactionEngine transactionEngine;

int main()
{
    std::cout << "VirtualMoneySystem v1.0.0 - Starting...\n\n";
    
    // Initialize database
    try {
        dbManager.initialize();
        std::cout << "[OK] Database initialized\n";
    } catch (const std::runtime_error& e) {
        std::cerr << "[ERROR] Database initialization failed: " << e.what() << "\n";
        return 1;
    }

    // Initialize scheduler
    JobScheduler scheduler;
    RecurringPayments recurringPayments(transactionEngine, dbManager);
    scheduler.schedule([&recurringPayments]() {
        recurringPayments.processPayments();
    }, 60);
    scheduler.start();
    std::cout << "[OK] Scheduler started\n";

    // Initialize analytics
    TransactionStats transactionStats(transactionEngine);
    FraudSignalDetector fraudDetector(transactionEngine);
    std::cout << "[OK] Analytics initialized\n";

    // Initialize transaction limits
    TransactionLimits transactionLimits(50000.0);
    std::cout << "[OK] Transaction limits configured\n";

    // Initialize API
    WalletEndpoints walletEndpoints(dbManager, transactionEngine, dbMutex, 
                                   transactionStats, fraudDetector, transactionLimits);
    RESTServer server(walletEndpoints);
    std::cout << "[OK] API server ready\n\n";

    // Use random port to avoid conflicts
    srand(time(0));
    int port = 10000 + (rand() % 10000);
    
    std::cout << "========================================\n";
    std::cout << "VirtualMoneySystem is RUNNING\n";
    std::cout << "========================================\n";
    std::cout << "API Server: http://localhost:" << port << "\n";
    std::cout << "Press Ctrl+C to stop\n";
    std::cout << "========================================\n\n";
    
    server.run(port);
    
    scheduler.stop();
    return 0;
}
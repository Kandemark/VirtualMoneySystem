cmake_minimum_required(VERSION 3.16)
project(VirtualMoneySystem)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Vendored SQLite3
add_library(sqlite3_lib vendor/sqlite3/sqlite3.c)

add_library(core_lib
    core/Wallet.cpp
    core/TransactionEngine.cpp
    core/CurrencyRegistry.cpp
    core/ExchangeRates.cpp
    core/LedgerManager.cpp
    core/RetryQueue.cpp
    core/RollbackManager.cpp
    core/TransactionProcessor.cpp
    core/EconomyZoneManager.cpp
)

add_library(transactions_lib
    transactions/Transaction.cpp
    transactions/TransactionLimits.cpp
    transactions/ReceiptGenerator.cpp
)

add_library(database_lib
    database/DatabaseManager.cpp
    database/BackupManager.cpp
    database/DatabaseConnector.cpp
    database/SQLiteDriver.cpp
    database/MigrationTools.cpp
    database/ORM.cpp
)

add_library(scheduler_lib
    scheduler/JobScheduler.cpp
    scheduler/CronEngine.cpp
    scheduler/RecurringPayments.cpp
)

add_library(compliance_lib
    compliance/KYCValidator.cpp
    compliance/AMLScanner.cpp
)

add_library(api_lib
    api/RESTServer.cpp
    api/WalletEndpoints.cpp
)

add_library(analytics_lib
    analytics/TransactionStats.cpp
    analytics/FraudSignalDetector.cpp
    analytics/UsageTracker.cpp
    analytics/LiquidityMonitor.cpp
    analytics/AccountInsights.cpp
    analytics/SegmentedStats.cpp
    analytics/UsageAnalytics.cpp
    analytics/BusinessInsights.cpp
    analytics/DashboardData.cpp
    analytics/ExposureReport.cpp
    analytics/HeatmapGenerator.cpp
    analytics/TrendGraphs.cpp
    analytics/InsightsDashboard.cpp
    analytics/VisualReports.cpp
)

add_executable(VirtualMoneySystem main.cpp)

target_include_directories(VirtualMoneySystem PRIVATE
    core
    transactions
    database
    scheduler
    compliance
    api
    analytics
    vendor/asio
    vendor/crow
    vendor/sqlite3 # Add sqlite3 include directory
)

target_link_libraries(VirtualMoneySystem PRIVATE
    core_lib
    transactions_lib
    database_lib
    scheduler_lib
    compliance_lib
    api_lib
    analytics_lib
    -lpthread
    sqlite3_lib # Link sqlite3 library
)

# Enable testing
enable_testing()

# Wallet tests
add_executable(test_wallet tests/test_wallet.cpp)
target_link_libraries(test_wallet PRIVATE core_lib)
target_include_directories(test_wallet PRIVATE vendor/asio vendor/crow)
add_test(NAME TestWallet COMMAND test_wallet)

# TransactionEngine tests
add_executable(test_transaction_engine tests/test_transaction_engine.cpp)
target_link_libraries(test_transaction_engine PRIVATE core_lib transactions_lib)
target_include_directories(test_transaction_engine PRIVATE vendor/asio vendor/crow)
add_test(NAME TestTransactionEngine COMMAND test_transaction_engine)

# API tests
add_executable(test_api tests/test_api.cpp)
# Generate a random port for the API test to avoid conflicts.
string(RANDOM LENGTH 4 ALPHABET "0123456789" RANDOM_PORT_SUFFIX)
set(API_TEST_PORT "1${RANDOM_PORT_SUFFIX}")
add_test(NAME TestAPI COMMAND test_api ${API_TEST_PORT})
set_tests_properties(TestAPI PROPERTIES DEPENDS VirtualMoneySystem)

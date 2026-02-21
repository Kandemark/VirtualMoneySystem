cmake_minimum_required(VERSION 3.16)
project(VirtualMoneySystem)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# MSVC compatible flags
if(MSVC)
    add_compile_options(/W3)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
else()
    add_compile_options(-Wall)
endif()

# Include directories
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/vendor)

# Core working libraries only - fully independent
add_library(core_lib
    core/Wallet.cpp
    core/TransactionEngine.cpp
    transactions/Transaction.cpp
)

add_library(database_lib
    database/DatabaseManager.cpp
    database/BackupManager.cpp
    database/ConnectionPool.cpp
)

add_library(transactions_lib
    transactions/TransactionPool.cpp
    transactions/ReceiptGenerator.cpp
    transactions/TransactionLimits.cpp
)

add_library(scheduler_lib
    scheduler/JobScheduler.cpp
    scheduler/CronEngine.cpp
    scheduler/RecurringPayments.cpp
)

add_library(auth_lib
    auth/JWTManager.cpp
    auth/PasswordHash.cpp
    auth/UserManager.cpp
    security/InputValidator.cpp
)

add_library(api_lib
    api/HTTPServer.cpp
    api/RESTServer.cpp
    api/WalletEndpoints.cpp
)

add_library(currency_lib
    currency/CurrencyExchange.cpp
    currency/ConversionEngine.cpp
    currency/CurrencyRegistry.cpp
    currency/FXRateFetcher.cpp
    currency/FXCacheManager.cpp
    currency/FXHistoryLogger.cpp
    currency/ExchangeRates.cpp
)

add_library(fees_lib
    fees/FeeEngine.cpp
    fees/FeePolicies.cpp
    fees/FeeSummaryGenerator.cpp
)

add_library(analytics_lib
    analytics/TransactionStats.cpp
    analytics/FraudSignalDetector.cpp
)

# Main executable
add_executable(VirtualMoneySystem
    main.cpp
)

# Link libraries
target_link_libraries(VirtualMoneySystem
    core_lib
    database_lib
    transactions_lib
    scheduler_lib
    auth_lib
    api_lib
    analytics_lib
    currency_lib
    fees_lib
)

message(STATUS "========================================")
message(STATUS "VirtualMoneySystem - Independent Build")
message(STATUS "========================================")
message(STATUS "ZERO external dependencies")
message(STATUS "Fully self-contained system")
message(STATUS "========================================")

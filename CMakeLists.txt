cmake_minimum_required(VERSION 3.16)
project(VirtualMoneySystem)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(core_lib
    core/Wallet.cpp
    core/TransactionEngine.cpp
)

add_library(transactions_lib
    transactions/Transaction.cpp
)

add_executable(VirtualMoneySystem main.cpp)

target_link_libraries(VirtualMoneySystem PRIVATE
    core_lib
    transactions_lib
)

target_include_directories(VirtualMoneySystem PRIVATE
    core
    transactions
)

# Enable testing
enable_testing()

# Wallet tests
add_executable(test_wallet tests/test_wallet.cpp)
target_link_libraries(test_wallet PRIVATE core_lib)
add_test(NAME TestWallet COMMAND test_wallet)

# TransactionEngine tests
add_executable(test_transaction_engine tests/test_transaction_engine.cpp)
target_link_libraries(test_transaction_engine PRIVATE core_lib transactions_lib)
add_test(NAME TestTransactionEngine COMMAND test_transaction_engine)

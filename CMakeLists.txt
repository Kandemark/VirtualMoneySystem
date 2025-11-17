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

target_include_directories(VirtualMoneySystem PRIVATE
    core
    transactions
    vendor/asio
    vendor/crow
)

target_link_libraries(VirtualMoneySystem PRIVATE
    core_lib
    transactions_lib
    -lpthread
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
add_test(NAME TestAPI COMMAND test_api)
set_tests_properties(TestAPI PROPERTIES DEPENDS VirtualMoneySystem)

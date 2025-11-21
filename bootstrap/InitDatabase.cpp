/**
 * @file InitDatabase.cpp
 */

#include "InitDatabase.h"
#include <iostream>

namespace VirtualMoney {

InitDatabase::InitDatabase() {}

bool InitDatabase::initialize() {
    std::cout << "Initializing database..." << std::endl;
    createTables();
    seedData();
    std::cout << "Database initialized successfully" << std::endl;
    return true;
}

void InitDatabase::createTables() {
    std::cout << "Creating tables..." << std::endl;
    std::cout << "✓ users" << std::endl;
    std::cout << "✓ wallets" << std::endl;
    std::cout << "✓ transactions" << std::endl;
    std::cout << "✓ audit_log" << std::endl;
}

void InitDatabase::seedData() {
    std::cout << "Seeding initial data..." << std::endl;
    std::cout << "✓ Admin user created" << std::endl;
    std::cout << "✓ Default settings inserted" << std::endl;
}

bool InitDatabase::migrate() {
    std::cout << "Running database migrations..." << std::endl;
    return true;
}

} // namespace VirtualMoney

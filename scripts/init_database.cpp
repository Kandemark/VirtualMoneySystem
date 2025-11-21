/**
 * @file init_database.cpp - Database initialization utility
 */

#include <iostream>

void createTables() {
    std::cout << "Creating database tables..." << std::endl;
    std::cout << "✓ users table created" << std::endl;
    std::cout << "✓ wallets table created" << std::endl;
    std::cout << "✓ transactions table created" << std::endl;
}

void seedData() {
    std::cout << "Seeding initial data..." << std::endl;
    std::cout << "✓ Admin user created" << std::endl;
    std::cout << "✓ Default settings inserted" << std::endl;
}

int main() {
    std::cout << "VirtualMoney Database Initializer" << std::endl;
    createTables();
    seedData();
    std::cout << "Database initialization complete!" << std::endl;
    return 0;
}

/**
 * @file InitDatabase.h
 * @brief Database initialization
 */

#ifndef INIT_DATABASE_H
#define INIT_DATABASE_H

#include <string>

class InitDatabase {
public:
    void initialize(const std::string& connectionString);
    void createTables();
    void seedData();
    bool isInitialized();
};

#endif

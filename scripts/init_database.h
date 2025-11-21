/**
 * @file init_database.h
 * @brief Database initialization script
 */

#ifndef INIT_DATABASE_SCRIPT_H
#define INIT_DATABASE_SCRIPT_H

#include <string>

void initializeDatabase(const std::string& connectionString);
void createAllTables();
void seedInitialData();

#endif

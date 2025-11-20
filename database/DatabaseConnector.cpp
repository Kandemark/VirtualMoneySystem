#include "DatabaseConnector.h"
#include <iostream>

DatabaseConnector::DatabaseConnector(const std::string& dbPath)
    : dbPath(dbPath), connection(nullptr), connected(false) {}

DatabaseConnector::~DatabaseConnector() {
    disconnect();
}

bool DatabaseConnector::connect() {
    if (connected) {
        return true;
    }

    int result = sqlite3_open(dbPath.c_str(), &connection);
    if (result != SQLITE_OK) {
        std::cerr << "Failed to open database: " << sqlite3_errmsg(connection) << std::endl;
        connection = nullptr;
        return false;
    }

    connected = true;
    return true;
}

void DatabaseConnector::disconnect() {
    if (connection) {
        sqlite3_close(connection);
        connection = nullptr;
        connected = false;
    }
}

bool DatabaseConnector::isConnected() const {
    return connected;
}

sqlite3* DatabaseConnector::getConnection() const {
    return connection;
}

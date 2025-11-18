#include "DatabaseManager.h"
#include <iostream>
#include <stdexcept>

// Constructor: Opens the database connection.
DatabaseManager::DatabaseManager(const std::string& dbPath) : db(nullptr) {
    if (sqlite3_open(dbPath.c_str(), &db)) {
        std::string errMsg = "Can't open database: ";
        errMsg += sqlite3_errmsg(db);
        throw std::runtime_error(errMsg);
    }
}

// Destructor: Closes the database connection.
DatabaseManager::~DatabaseManager() {
    if (db) {
        sqlite3_close(db);
    }
}

// Initializes the database by creating the required tables.
void DatabaseManager::initialize() {
    char* errMsg = nullptr;
    const char* sql = "CREATE TABLE IF NOT EXISTS wallets ("
                      "user_id TEXT PRIMARY KEY NOT NULL,"
                      "currency TEXT NOT NULL,"
                      "balance REAL NOT NULL);";

    if (sqlite3_exec(db, sql, 0, 0, &errMsg)) {
        std::string error = "SQL error: ";
        error += errMsg;
        sqlite3_free(errMsg);
        throw std::runtime_error(error);
    }
}

// Creates a new wallet in the database.
bool DatabaseManager::createWallet(const Wallet& wallet) {
    sqlite3_stmt* stmt;
    const char* sql = "INSERT INTO wallets (user_id, currency, balance) VALUES (?, ?, ?);";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        return false;
    }

    sqlite3_bind_text(stmt, 1, wallet.getUserId().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, wallet.getCurrency().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 3, wallet.getBalance());

    bool success = sqlite3_step(stmt) == SQLITE_DONE;

    sqlite3_finalize(stmt);
    return success;
}

// Retrieves a wallet from the database by user ID.
std::optional<Wallet> DatabaseManager::getWallet(const std::string& userId) {
    sqlite3_stmt* stmt;
    const char* sql = "SELECT currency, balance FROM wallets WHERE user_id = ?;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        return std::nullopt;
    }

    sqlite3_bind_text(stmt, 1, userId.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        std::string currency = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        double balance = sqlite3_column_double(stmt, 1);

        Wallet wallet(userId, currency, balance);
        sqlite3_finalize(stmt);
        return wallet;
    }

    sqlite3_finalize(stmt);
    return std::nullopt;
}

// Updates the balance of a wallet in the database.
bool DatabaseManager::updateWalletBalance(const std::string& userId, double newBalance) {
    sqlite3_stmt* stmt;
    const char* sql = "UPDATE wallets SET balance = ? WHERE user_id = ?;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        return false;
    }

    sqlite3_bind_double(stmt, 1, newBalance);
    sqlite3_bind_text(stmt, 2, userId.c_str(), -1, SQLITE_STATIC);

    bool success = sqlite3_step(stmt) == SQLITE_DONE;

    if (success) {
        success = sqlite3_changes(db) > 0;
    }

    sqlite3_finalize(stmt);
    return success;
}

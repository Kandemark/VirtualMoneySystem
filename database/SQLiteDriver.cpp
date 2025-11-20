#include "SQLiteDriver.h"
#include <iostream>

SQLiteDriver::SQLiteDriver(sqlite3* db) : db(db) {}

bool SQLiteDriver::executeQuery(const std::string& query) {
    char* errorMessage = nullptr;
    int result = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errorMessage);

    if (result != SQLITE_OK) {
        std::cerr << "SQL error: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
        return false;
    }

    return true;
}

std::vector<std::map<std::string, std::string>> SQLiteDriver::executeSelect(const std::string& query) {
    std::vector<std::map<std::string, std::string>> results;
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return results;
    }

    int columnCount = sqlite3_column_count(stmt);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        std::map<std::string, std::string> row;
        for (int i = 0; i < columnCount; i++) {
            const char* columnName = sqlite3_column_name(stmt, i);
            const unsigned char* columnValue = sqlite3_column_text(stmt, i);
            row[columnName] = columnValue ? reinterpret_cast<const char*>(columnValue) : "";
        }
        results.push_back(row);
    }

    sqlite3_finalize(stmt);
    return results;
}

int SQLiteDriver::getLastInsertId() {
    return sqlite3_last_insert_rowid(db);
}

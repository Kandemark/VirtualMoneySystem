#include "ORM.h"
#include <iostream>
#include <sstream>

ORM::ORM(sqlite3* db) : db(db) {}

bool ORM::insert(const std::string& table, const std::map<std::string, std::string>& data) {
    std::string query = buildInsertQuery(table, data);
    char* errorMessage = nullptr;
    int result = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errorMessage);

    if (result != SQLITE_OK) {
        std::cerr << "Insert failed: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
        return false;
    }

    return true;
}

std::vector<std::map<std::string, std::string>> ORM::select(const std::string& table, const std::string& whereClause) {
    std::vector<std::map<std::string, std::string>> results;
    std::string query = "SELECT * FROM " + table;
    if (!whereClause.empty()) {
        query += " WHERE " + whereClause;
    }

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare select: " << sqlite3_errmsg(db) << std::endl;
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

bool ORM::update(const std::string& table, const std::map<std::string, std::string>& data, const std::string& whereClause) {
    std::string query = buildUpdateQuery(table, data, whereClause);
    char* errorMessage = nullptr;
    int result = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errorMessage);

    if (result != SQLITE_OK) {
        std::cerr << "Update failed: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
        return false;
    }

    return true;
}

bool ORM::deleteRecord(const std::string& table, const std::string& whereClause) {
    std::string query = "DELETE FROM " + table;
    if (!whereClause.empty()) {
        query += " WHERE " + whereClause;
    }

    char* errorMessage = nullptr;
    int result = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errorMessage);

    if (result != SQLITE_OK) {
        std::cerr << "Delete failed: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
        return false;
    }

    return true;
}

std::string ORM::buildInsertQuery(const std::string& table, const std::map<std::string, std::string>& data) {
    std::ostringstream columns, values;
    bool first = true;

    for (const auto& [key, value] : data) {
        if (!first) {
            columns << ", ";
            values << ", ";
        }
        columns << key;
        values << "'" << value << "'";
        first = false;
    }

    return "INSERT INTO " + table + " (" + columns.str() + ") VALUES (" + values.str() + ")";
}

std::string ORM::buildUpdateQuery(const std::string& table, const std::map<std::string, std::string>& data, const std::string& whereClause) {
    std::ostringstream sets;
    bool first = true;

    for (const auto& [key, value] : data) {
        if (!first) {
            sets << ", ";
        }
        sets << key << " = '" << value << "'";
        first = false;
    }

    std::string query = "UPDATE " + table + " SET " + sets.str();
    if (!whereClause.empty()) {
        query += " WHERE " + whereClause;
    }

    return query;
}

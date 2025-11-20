#include "MigrationTools.h"
#include <iostream>

MigrationTools::MigrationTools(sqlite3* db) : db(db) {}

bool MigrationTools::initMigrationTable() {
    const char* createTableSQL = R"(
        CREATE TABLE IF NOT EXISTS schema_migrations (
            version INTEGER PRIMARY KEY,
            applied_at DATETIME DEFAULT CURRENT_TIMESTAMP
        );
    )";

    char* errorMessage = nullptr;
    int result = sqlite3_exec(db, createTableSQL, nullptr, nullptr, &errorMessage);

    if (result != SQLITE_OK) {
        std::cerr << "Failed to create migration table: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
        return false;
    }

    return true;
}

int MigrationTools::getCurrentVersion() {
    sqlite3_stmt* stmt;
    const char* query = "SELECT MAX(version) FROM schema_migrations";

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        return 0;
    }

    int version = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        version = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);
    return version;
}

bool MigrationTools::migrate(int targetVersion, const std::vector<Migration>& migrations) {
    int currentVersion = getCurrentVersion();

    for (const auto& migration : migrations) {
        if (migration.version > currentVersion && migration.version <= targetVersion) {
            std::cout << "Applying migration " << migration.version << ": " << migration.description << std::endl;
            if (!executeMigration(migration, true)) {
                return false;
            }
            if (!updateVersion(migration.version)) {
                return false;
            }
        }
    }

    return true;
}

bool MigrationTools::rollback(int targetVersion, const std::vector<Migration>& migrations) {
    int currentVersion = getCurrentVersion();

    for (auto it = migrations.rbegin(); it != migrations.rend(); ++it) {
        if (it->version <= currentVersion && it->version > targetVersion) {
            std::cout << "Rolling back migration " << it->version << ": " << it->description << std::endl;
            if (!executeMigration(*it, false)) {
                return false;
            }
            // Remove version record
            std::string deleteQuery = "DELETE FROM schema_migrations WHERE version = " + std::to_string(it->version);
            char* errorMessage = nullptr;
            sqlite3_exec(db, deleteQuery.c_str(), nullptr, nullptr, &errorMessage);
            if (errorMessage) {
                sqlite3_free(errorMessage);
                return false;
            }
        }
    }

    return true;
}

bool MigrationTools::executeMigration(const Migration& migration, bool isUp) {
    const std::string& query = isUp ? migration.upQuery : migration.downQuery;
    char* errorMessage = nullptr;
    int result = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errorMessage);

    if (result != SQLITE_OK) {
        std::cerr << "Migration failed: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
        return false;
    }

    return true;
}

bool MigrationTools::updateVersion(int version) {
    std::string insertQuery = "INSERT INTO schema_migrations (version) VALUES (" + std::to_string(version) + ")";
    char* errorMessage = nullptr;
    int result = sqlite3_exec(db, insertQuery.c_str(), nullptr, nullptr, &errorMessage);

    if (result != SQLITE_OK) {
        std::cerr << "Failed to update version: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
        return false;
    }

    return true;
}

#ifndef MIGRATION_TOOLS_H
#define MIGRATION_TOOLS_H

#include <string>
#include <vector>
#include <sqlite3.h>

struct Migration {
    int version;
    std::string description;
    std::string upQuery;
    std::string downQuery;
};

class MigrationTools {
public:
    MigrationTools(sqlite3* db);

    bool initMigrationTable();
    int getCurrentVersion();
    bool migrate(int targetVersion, const std::vector<Migration>& migrations);
    bool rollback(int targetVersion, const std::vector<Migration>& migrations);

private:
    sqlite3* db;
    bool executeMigration(const Migration& migration, bool isUp);
    bool updateVersion(int version);
};

#endif // MIGRATION_TOOLS_H

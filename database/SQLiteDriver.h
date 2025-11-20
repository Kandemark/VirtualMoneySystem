#ifndef SQLITE_DRIVER_H
#define SQLITE_DRIVER_H

#include <string>
#include <vector>
#include <map>
#include <sqlite3.h>

class SQLiteDriver {
public:
    SQLiteDriver(sqlite3* db);

    bool executeQuery(const std::string& query);
    std::vector<std::map<std::string, std::string>> executeSelect(const std::string& query);
    int getLastInsertId();

private:
    sqlite3* db;
};

#endif // SQLITE_DRIVER_H

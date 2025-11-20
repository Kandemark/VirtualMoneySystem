#ifndef ORM_H
#define ORM_H

#include <string>
#include <map>
#include <vector>
#include <sqlite3.h>

class ORM {
public:
    ORM(sqlite3* db);

    // Generic CRUD operations
    bool insert(const std::string& table, const std::map<std::string, std::string>& data);
    std::vector<std::map<std::string, std::string>> select(const std::string& table, const std::string& whereClause = "");
    bool update(const std::string& table, const std::map<std::string, std::string>& data, const std::string& whereClause);
    bool deleteRecord(const std::string& table, const std::string& whereClause);

private:
    sqlite3* db;
    std::string buildInsertQuery(const std::string& table, const std::map<std::string, std::string>& data);
    std::string buildUpdateQuery(const std::string& table, const std::map<std::string, std::string>& data, const std::string& whereClause);
};

#endif // ORM_H

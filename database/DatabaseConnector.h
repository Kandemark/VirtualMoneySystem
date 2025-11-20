#ifndef DATABASE_CONNECTOR_H
#define DATABASE_CONNECTOR_H

#include <string>
#include <memory>
#include <sqlite3.h>

class DatabaseConnector {
public:
    DatabaseConnector(const std::string& dbPath);
    ~DatabaseConnector();

    bool connect();
    void disconnect();
    bool isConnected() const;
    sqlite3* getConnection() const;

private:
    std::string dbPath;
    sqlite3* connection;
    bool connected;
};

#endif // DATABASE_CONNECTOR_H

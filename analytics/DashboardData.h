#ifndef DASHBOARD_DATA_H
#define DASHBOARD_DATA_H

#include "../core/TransactionEngine.h"
#include "../database/DatabaseManager.h"
#include <string>
#include <map>

struct DashboardMetrics {
    int totalUsers;
    int totalTransactions;
    double totalVolume;
    int activeUsersToday;
    std::map<std::string, double> volumeByCurrency;
};

class DashboardData {
public:
    DashboardData(const TransactionEngine& transactionEngine, DatabaseManager& dbManager);

    DashboardMetrics getMetrics() const;

private:
    const TransactionEngine& transactionEngine;
    DatabaseManager& dbManager;
};

#endif // DASHBOARD_DATA_H

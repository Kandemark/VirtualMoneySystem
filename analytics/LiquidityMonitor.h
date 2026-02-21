#ifndef LIQUIDITY_MONITOR_H
#define LIQUIDITY_MONITOR_H

#include "../database/DatabaseManager.h"
#include <string>
#include <map>
#include <mutex>

class LiquidityMonitor {
public:
    LiquidityMonitor(DatabaseManager& dbManager);

    double getTotalLiquidity(const std::string& currency) const;
    std::map<std::string, double> getLiquidityByCurrency() const;
    double getAverageLiquidity() const;

private:
    DatabaseManager& dbManager;
};

#endif // LIQUIDITY_MONITOR_H

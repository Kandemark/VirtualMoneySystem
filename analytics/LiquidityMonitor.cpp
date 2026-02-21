#include "LiquidityMonitor.h"

LiquidityMonitor::LiquidityMonitor(DatabaseManager& dbManager)
    : dbManager(dbManager) {}

double LiquidityMonitor::getTotalLiquidity(const std::string& currency) const {
    double total = 0.0;

    const auto balances = dbManager.getAllWalletBalances();
    const auto currencies = dbManager.getAllWalletCurrencies();
    for (const auto& pair : balances) {
        const auto it = currencies.find(pair.first);
        if (it != currencies.end() && it->second == currency) {
            total += pair.second;
        }
    }
    
    return total;
}

std::map<std::string, double> LiquidityMonitor::getLiquidityByCurrency() const {
    std::map<std::string, double> liquidity;

    const auto balances = dbManager.getAllWalletBalances();
    const auto currencies = dbManager.getAllWalletCurrencies();
    for (const auto& pair : balances) {
        const auto it = currencies.find(pair.first);
        if (it != currencies.end()) {
            liquidity[it->second] += pair.second;
        }
    }
    
    return liquidity;
}

double LiquidityMonitor::getAverageLiquidity() const {
    const auto balances = dbManager.getAllWalletBalances();
    if (balances.empty()) {
        return 0.0;
    }
    
    double total = 0.0;
    for (const auto& pair : balances) {
        total += pair.second;
    }
    
    return total / balances.size();
}

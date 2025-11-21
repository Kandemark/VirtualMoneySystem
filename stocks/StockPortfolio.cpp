#include "StockPortfolio.h"

void StockPortfolio::addHolding(const std::string& userId, const std::string& symbol, int shares, double price) {
    Holding holding;
    holding.symbol = symbol;
    holding.shares = shares;
    holding.avgPurchasePrice = price;
    holding.currentPrice = price;
    portfolios[userId].push_back(holding);
}

void StockPortfolio::removeHolding(const std::string& userId, const std::string& symbol, int shares) {
    auto& holdings = portfolios[userId];
    for (auto it = holdings.begin(); it != holdings.end(); ++it) {
        if (it->symbol == symbol) {
            it->shares -= shares;
            if (it->shares <= 0) {
                holdings.erase(it);
            }
            break;
        }
    }
}

std::vector<Holding> StockPortfolio::getPortfolio(const std::string& userId) {
    return portfolios[userId];
}

double StockPortfolio::getPortfolioValue(const std::string& userId) {
    double total = 0.0;
    for (const auto& holding : portfolios[userId]) {
        total += holding.shares * holding.currentPrice;
    }
    return total;
}

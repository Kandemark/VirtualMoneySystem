/**
 * @file StockPortfolio.h
 * @brief Manages user stock portfolios and holdings
 */

#ifndef STOCK_PORTFOLIO_H
#define STOCK_PORTFOLIO_H

#include <string>
#include <map>
#include <vector>

struct Holding {
    std::string symbol;
    int shares;
    double avgPurchasePrice;
    double currentPrice;
};

class StockPortfolio {
public:
    void addHolding(const std::string& userId, const std::string& symbol, int shares, double price);
    void removeHolding(const std::string& userId, const std::string& symbol, int shares);
    std::vector<Holding> getPortfolio(const std::string& userId);
    double getPortfolioValue(const std::string& userId);
private:
    std::map<std::string, std::vector<Holding>> portfolios;
};

#endif

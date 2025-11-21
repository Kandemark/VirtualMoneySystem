/**
 * @file MarketSummary.cpp
 */

#include "MarketSummary.h"
#include <iostream>

MarketSummary::MarketSummary() {}

void MarketSummary::updatePrice(const std::string& symbol, double price) {
    prices[symbol] = price;
}

double MarketSummary::getPrice(const std::string& symbol) const {
    auto it = prices.find(symbol);
    if (it != prices.end()) {
        return it->second;
    }
    return 0.0;
}

std::map<std::string, double> MarketSummary::getAllPrices() const {
    return prices;
}

double MarketSummary::getMarketCap() const {
    double total = 0.0;
    for (const auto& [symbol, price] : prices) {
        total += price * 1000000; // Simplified
    }
    return total;
}

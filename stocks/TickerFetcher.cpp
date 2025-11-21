/**
 * @file TickerFetcher.cpp
 */

#include "TickerFetcher.h"
#include <iostream>
#include <random>

TickerFetcher::TickerFetcher() {}

double TickerFetcher::fetchPrice(const std::string& symbol) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(100.0, 500.0);
    
    double price = dis(gen);
    std::cout << "Fetched price for " << symbol << ": $" << price << std::endl;
    
    return price;
}

std::map<std::string, double> TickerFetcher::fetchMultiple(const std::vector<std::string>& symbols) {
    std::map<std::string, double> prices;
    
    for (const auto& symbol : symbols) {
        prices[symbol] = fetchPrice(symbol);
    }
    
    return prices;
}

bool TickerFetcher::isMarketOpen() const {
    // Simplified - check if market hours
    return true;
}

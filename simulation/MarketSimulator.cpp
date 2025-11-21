/**
 * @file MarketSimulator.cpp
 */

#include "MarketSimulator.h"
#include <iostream>
#include <random>

MarketSimulator::MarketSimulator() {}

void MarketSimulator::addStock(const std::string& symbol, double initialPrice) {
    stocks[symbol] = initialPrice;
    std::cout << "Stock added: " << symbol << " @ $" << initialPrice << std::endl;
}

void MarketSimulator::simulateMarket(int ticks) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-0.05, 0.05);
    
    for (int i = 0; i < ticks; ++i) {
        for (auto& [symbol, price] : stocks) {
            double change = price * dis(gen);
            price += change;
            
            MarketTick tick;
            tick.symbol = symbol;
            tick.price = price;
            tick.change = change;
            tick.timestamp = std::time(nullptr);
            
            history.push_back(tick);
        }
    }
    
    std::cout << "Market simulation complete: " << ticks << " ticks" << std::endl;
}

double MarketSimulator::getPrice(const std::string& symbol) const {
    auto it = stocks.find(symbol);
    if (it != stocks.end()) {
        return it->second;
    }
    return 0.0;
}

std::vector<MarketTick> MarketSimulator::getHistory() const {
    return history;
}

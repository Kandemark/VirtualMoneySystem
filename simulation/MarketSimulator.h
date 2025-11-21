/**
 * @file MarketSimulator.h
 * @brief Market behavior simulation
 */

#ifndef MARKET_SIMULATOR_H
#define MARKET_SIMULATOR_H

#include <string>

class MarketSimulator {
public:
    void simulateMarket(int days);
    double getPriceAtDay(const std::string& asset, int day);
    void setVolatility(double volatility);
    void addMarketEvent(const std::string& eventType, int day);
};

#endif

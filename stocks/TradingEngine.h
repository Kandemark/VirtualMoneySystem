/**
 * @file TradingEngine.h
 * @brief Executes stock buy/sell orders
 */

#ifndef TRADING_ENGINE_H
#define TRADING_ENGINE_H

#include <string>

class TradingEngine {
public:
    bool executeBuy(const std::string& userId, const std::string& symbol, int shares, double price);
    bool executeSell(const std::string& userId, const std::string& symbol, int shares, double price);
    std::string placeOrder(const std::string& userId, const std::string& symbol, int shares, const std::string& orderType);
};

#endif

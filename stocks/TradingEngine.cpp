#include "TradingEngine.h"
#include <iostream>

bool TradingEngine::executeBuy(const std::string& userId, const std::string& symbol, int shares, double price) {
    std::cout << "[Trading] BUY " << shares << " shares of " << symbol << " at $" << price << std::endl;
    return true;
}

bool TradingEngine::executeSell(const std::string& userId, const std::string& symbol, int shares, double price) {
    std::cout << "[Trading] SELL " << shares << " shares of " << symbol << " at $" << price << std::endl;
    return true;
}

std::string TradingEngine::placeOrder(const std::string& userId, const std::string& symbol, int shares, const std::string& orderType) {
    return "ORDER_" + symbol + "_" + std::to_string(shares);
}

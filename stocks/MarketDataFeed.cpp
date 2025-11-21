#include "MarketDataFeed.h"

double MarketDataFeed::getStockPrice(const std::string& symbol) {
    auto it = prices.find(symbol);
    return (it != prices.end()) ? it->second : 100.0;
}

void MarketDataFeed::updatePrice(const std::string& symbol, double price) {
    if (openPrices.find(symbol) == openPrices.end()) {
        openPrices[symbol] = price;
    }
    prices[symbol] = price;
}

double MarketDataFeed::getDayChange(const std::string& symbol) {
    double current = getStockPrice(symbol);
    auto it = openPrices.find(symbol);
    if (it != openPrices.end()) {
        return ((current - it->second) / it->second) * 100.0;
    }
    return 0.0;
}

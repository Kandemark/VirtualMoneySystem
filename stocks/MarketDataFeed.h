/**
 * @file MarketDataFeed.h
 * @brief Real-time stock market data feed
 */

#ifndef MARKET_DATA_FEED_H
#define MARKET_DATA_FEED_H

#include <string>
#include <map>

class MarketDataFeed {
public:
    double getStockPrice(const std::string& symbol);
    void updatePrice(const std::string& symbol, double price);
    double getDayChange(const std::string& symbol);
private:
    std::map<std::string, double> prices;
    std::map<std::string, double> openPrices;
};

#endif

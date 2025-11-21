/**
 * @file TickerFetcher.h
 * @brief Stock ticker data fetcher
 */

#ifndef TICKER_FETCHER_H
#define TICKER_FETCHER_H

#include <string>

class TickerFetcher {
public:
    double getPrice(const std::string& symbol);
    std::string getTickerData(const std::string& symbol);
    void updatePrices();
};

#endif

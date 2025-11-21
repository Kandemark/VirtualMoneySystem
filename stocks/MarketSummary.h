/**
 * @file MarketSummary.h
 * @brief Stock market summary
 */

#ifndef MARKET_SUMMARY_H
#define MARKET_SUMMARY_H

#include <string>

class MarketSummary {
public:
    std::string getSummary();
    std::string getTopGainers();
    std::string getTopLosers();
};

#endif

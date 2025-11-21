/**
 * @file StockWallet.h
 * @brief Stock portfolio wallet
 */

#ifndef STOCK_WALLET_H
#define STOCK_WALLET_H

#include <string>
#include <map>

class StockWallet {
public:
    void buyStock(const std::string& symbol, int quantity);
    void sellStock(const std::string& symbol, int quantity);
    std::map<std::string, int> getHoldings();
};

#endif

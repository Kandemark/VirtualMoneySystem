/**
 * @file WatchlistScanner.h
 * @brief Watchlist scanning for sanctions and PEPs
 */

#ifndef WATCHLIST_SCANNER_H
#define WATCHLIST_SCANNER_H

#include <string>

class WatchlistScanner {
public:
    bool checkWatchlist(const std::string& name, const std::string& country);
    void updateWatchlist(const std::string& watchlistData);
    std::string getWatchlistStatus(const std::string& userId);
};

#endif

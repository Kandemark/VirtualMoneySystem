#include "WatchlistScanner.h"

#include <unordered_set>

namespace { std::unordered_set<std::string> g_watchlist; }

bool WatchlistScanner::checkWatchlist(const std::string& name, const std::string& country) { return g_watchlist.count(name + ":" + country) > 0; }
void WatchlistScanner::updateWatchlist(const std::string& watchlistData) { g_watchlist.insert(watchlistData); }
std::string WatchlistScanner::getWatchlistStatus(const std::string& userId) { return g_watchlist.count(userId) ? "MATCH" : "CLEAR"; }

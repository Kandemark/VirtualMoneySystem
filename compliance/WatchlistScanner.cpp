#include "WatchlistScanner.h"

#include <unordered_set>

namespace {
std::unordered_set<std::string> g_watchlist;
std::unordered_set<std::string> g_flaggedUsers;
}

bool WatchlistScanner::checkWatchlist(const std::string& name, const std::string& country) {
    return g_watchlist.count(name + ":" + country) > 0;
}

void WatchlistScanner::updateWatchlist(const std::string& watchlistData) {
    // Supports either "name:country" entries or user IDs pre-flagged upstream.
    if (watchlistData.find(':') != std::string::npos) {
        g_watchlist.insert(watchlistData);
    } else if (!watchlistData.empty()) {
        g_flaggedUsers.insert(watchlistData);
    }
}

std::string WatchlistScanner::getWatchlistStatus(const std::string& userId) {
    return g_flaggedUsers.count(userId) ? "MATCH" : "CLEAR";
}

/**
 * @file SocialTradingPlatform.cpp
 */

#include "SocialTradingPlatform.h"
#include <iostream>
#include <algorithm>
#include <random>

namespace VirtualMoney {
namespace Social {

SocialTradingPlatform::SocialTradingPlatform() {
    std::cout << "Social Trading Platform initialized" << std::endl;
    
    // Create sample top traders
    Trader topTrader;
    topTrader.traderId = "TRADER_001";
    topTrader.username = "CryptoKing";
    topTrader.totalReturn = 125.5;
    topTrader.winRate = 72.0;
    topTrader.followers = 5000;
    topTrader.totalTrades = 500;
    topTrader.riskLevel = "medium";
    traders[topTrader.traderId] = topTrader;
}

std::string SocialTradingPlatform::followTrader(const std::string& followerId, const std::string& leaderId, double allocation) {
    std::string copyId = generateCopyId();
    
    CopyTrade copy;
    copy.copyId = copyId;
    copy.followerId = followerId;
    copy.leaderId = leaderId;
    copy.allocation = allocation;
    copy.active = true;
    
    copyTrades[copyId] = copy;
    
    // Add to followers list
    followers[leaderId].push_back(followerId);
    
    // Update follower count
    auto it = traders.find(leaderId);
    if (it != traders.end()) {
        it->second.followers++;
    }
    
    std::cout << "Copy trading started: " << followerId << " following " << leaderId << std::endl;
    std::cout << "  Allocation: " << allocation << "%" << std::endl;
    
    return copyId;
}

bool SocialTradingPlatform::unfollowTrader(const std::string& copyId) {
    auto it = copyTrades.find(copyId);
    if (it != copyTrades.end()) {
        it->second.active = false;
        
        // Update follower count
        auto traderIt = traders.find(it->second.leaderId);
        if (traderIt != traders.end()) {
            traderIt->second.followers--;
        }
        
        std::cout << "Copy trading stopped: " << copyId << std::endl;
        return true;
    }
    
    return false;
}

std::vector<LeaderboardEntry> SocialTradingPlatform::getLeaderboard(int limit) {
    std::vector<LeaderboardEntry> leaderboard;
    
    // Create sample leaderboard
    for (int i = 0; i < std::min(limit, 10); ++i) {
        LeaderboardEntry entry;
        entry.rank = i + 1;
        entry.traderId = "TRADER_" + std::to_string(i + 1);
        entry.username = "Trader" + std::to_string(i + 1);
        entry.return30d = 50.0 - (i * 5.0);
        entry.return90d = 100.0 - (i * 10.0);
        entry.return1y = 200.0 - (i * 20.0);
        entry.followers = 5000 - (i * 500);
        
        leaderboard.push_back(entry);
    }
    
    std::cout << "Leaderboard generated with " << leaderboard.size() << " entries" << std::endl;
    
    return leaderboard;
}

Trader SocialTradingPlatform::getTraderProfile(const std::string& traderId) {
    auto it = traders.find(traderId);
    if (it != traders.end()) {
        return it->second;
    }
    return Trader();
}

bool SocialTradingPlatform::shareTrade(const std::string& traderId, const std::string& tradeDetails) {
    std::cout << "Trade shared by " << traderId << ": " << tradeDetails << std::endl;
    return true;
}

std::vector<std::string> SocialTradingPlatform::getSocialFeed(const std::string& userId) {
    std::vector<std::string> feed;
    
    feed.push_back("CryptoKing bought BTC at $50,000 (+5% profit)");
    feed.push_back("TraderPro sold ETH at $3,000 (+10% profit)");
    feed.push_back("MoonShot opened long position on SOL");
    
    std::cout << "Social feed loaded: " << feed.size() << " posts" << std::endl;
    
    return feed;
}

std::string SocialTradingPlatform::createCompetition(const std::string& name, double prizePool, int durationDays) {
    std::string competitionId = "COMP_" + std::to_string(std::time(nullptr));
    
    std::cout << "Trading competition created: " << name << std::endl;
    std::cout << "  Prize Pool: $" << prizePool << std::endl;
    std::cout << "  Duration: " << durationDays << " days" << std::endl;
    
    return competitionId;
}

bool SocialTradingPlatform::joinCompetition(const std::string& competitionId, const std::string& traderId) {
    std::cout << "Trader " << traderId << " joined competition " << competitionId << std::endl;
    return true;
}

std::vector<std::string> SocialTradingPlatform::getFollowers(const std::string& traderId) {
    auto it = followers.find(traderId);
    if (it != followers.end()) {
        return it->second;
    }
    return {};
}

std::vector<std::string> SocialTradingPlatform::getFollowing(const std::string& traderId) {
    std::vector<std::string> following;
    
    for (const auto& [copyId, copy] : copyTrades) {
        if (copy.followerId == traderId && copy.active) {
            following.push_back(copy.leaderId);
        }
    }
    
    return following;
}

double SocialTradingPlatform::calculateTraderScore(const std::string& traderId) {
    auto it = traders.find(traderId);
    if (it != traders.end()) {
        const auto& trader = it->second;
        
        // Weighted score
        double score = 0.0;
        score += trader.totalReturn * 0.4;
        score += trader.winRate * 0.3;
        score += (trader.followers / 100.0) * 0.2;
        score += (trader.totalTrades / 10.0) * 0.1;
        
        return score;
    }
    
    return 0.0;
}

std::string SocialTradingPlatform::generateCopyId() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(100000, 999999);
    
    return "COPY_" + std::to_string(dis(gen));
}

} // namespace Social
} // namespace VirtualMoney

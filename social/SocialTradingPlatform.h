/**
 * @file SocialTradingPlatform.h
 * @brief Social trading with copy trading and leaderboards
 */

#ifndef SOCIAL_TRADING_PLATFORM_H
#define SOCIAL_TRADING_PLATFORM_H

#include <string>
#include <vector>
#include <map>

namespace VirtualMoney {
namespace Social {

struct Trader {
    std::string traderId;
    std::string username;
    double totalReturn;
    double winRate;
    int followers;
    int totalTrades;
    std::string riskLevel; // "low", "medium", "high"
};

struct CopyTrade {
    std::string copyId;
    std::string followerId;
    std::string leaderId;
    double allocation; // Percentage of portfolio
    bool active;
};

struct LeaderboardEntry {
    int rank;
    std::string traderId;
    std::string username;
    double return30d;
    double return90d;
    double return1y;
    int followers;
};

class SocialTradingPlatform {
public:
    SocialTradingPlatform();
    
    /**
     * @brief Follow a trader (copy trading)
     */
    std::string followTrader(const std::string& followerId, const std::string& leaderId, double allocation);
    
    /**
     * @brief Unfollow trader
     */
    bool unfollowTrader(const std::string& copyId);
    
    /**
     * @brief Get leaderboard
     */
    std::vector<LeaderboardEntry> getLeaderboard(int limit = 100);
    
    /**
     * @brief Get trader profile
     */
    Trader getTraderProfile(const std::string& traderId);
    
    /**
     * @brief Share trade
     */
    bool shareTrade(const std::string& traderId, const std::string& tradeDetails);
    
    /**
     * @brief Get social feed
     */
    std::vector<std::string> getSocialFeed(const std::string& userId);
    
    /**
     * @brief Create trading competition
     */
    std::string createCompetition(const std::string& name, double prizePool, int durationDays);
    
    /**
     * @brief Join competition
     */
    bool joinCompetition(const std::string& competitionId, const std::string& traderId);
    
    /**
     * @brief Get trader's followers
     */
    std::vector<std::string> getFollowers(const std::string& traderId);
    
    /**
     * @brief Get following list
     */
    std::vector<std::string> getFollowing(const std::string& traderId);
    
    /**
     * @brief Calculate trader score
     */
    double calculateTraderScore(const std::string& traderId);
    
private:
    std::map<std::string, Trader> traders;
    std::map<std::string, CopyTrade> copyTrades;
    std::map<std::string, std::vector<std::string>> followers; // traderId -> followerIds
    
    std::string generateCopyId();
};

} // namespace Social
} // namespace VirtualMoney

#endif

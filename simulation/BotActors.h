/**
 * @file BotActors.h
 * @brief Automated bot actors for simulation
 */

#ifndef BOT_ACTORS_H
#define BOT_ACTORS_H

#include <string>
#include <vector>

class BotActors {
public:
    void createBot(const std::string& botId, const std::string& behavior);
    void startBot(const std::string& botId);
    void stopBot(const std::string& botId);
    void setBotBehavior(const std::string& botId, const std::string& behavior);
    std::vector<std::string> getActiveBots();
};

#endif

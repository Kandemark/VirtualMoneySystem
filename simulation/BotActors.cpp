/**
 * @file BotActors.cpp
 * @brief Simulation bot actors implementation
 */

#include "BotActors.h"
#include <random>
#include <iostream>

namespace VirtualMoney {

BotActors::BotActors() : isRunning(false) {}

void BotActors::createBot(const std::string& botId, const std::string& behavior) {
    Bot bot;
    bot.botId = botId;
    bot.behavior = behavior;
    bot.balance = 10000.0; // Starting balance
    bot.transactionCount = 0;
    bot.active = true;
    
    bots[botId] = bot;
    
    std::cout << "Bot created: " << botId << " (behavior: " << behavior << ")" << std::endl;
}

void BotActors::startSimulation() {
    isRunning = true;
    
    std::cout << "Starting bot simulation with " << bots.size() << " bots..." << std::endl;
    
    // Simulate bot activities
    for (auto& [id, bot] : bots) {
        if (bot.active) {
            simulateBotActivity(bot);
        }
    }
}

void BotActors::stopSimulation() {
    isRunning = false;
    std::cout << "Bot simulation stopped" << std::endl;
}

std::vector<Bot> BotActors::getActiveBots() const {
    std::vector<Bot> activeBots;
    
    for (const auto& [id, bot] : bots) {
        if (bot.active) {
            activeBots.push_back(bot);
        }
    }
    
    return activeBots;
}

BotActors::SimulationStats BotActors::getStatistics() const {
    SimulationStats stats;
    stats.totalBots = bots.size();
    stats.activeBots = 0;
    stats.totalTransactions = 0;
    stats.totalVolume = 0.0;
    
    for (const auto& [id, bot] : bots) {
        if (bot.active) {
            stats.activeBots++;
        }
        stats.totalTransactions += bot.transactionCount;
    }
    
    return stats;
}

void BotActors::simulateBotActivity(Bot& bot) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> amountDis(10.0, 1000.0);
    std::uniform_int_distribution<> actionDis(0, 2);
    
    int action = actionDis(gen);
    double amount = amountDis(gen);
    
    if (bot.behavior == "trader") {
        // Simulate trading activity
        if (action == 0 && bot.balance >= amount) {
            bot.balance -= amount;
            bot.transactionCount++;
            std::cout << "Bot " << bot.botId << " sold $" << amount << std::endl;
        } else if (action == 1) {
            bot.balance += amount;
            bot.transactionCount++;
            std::cout << "Bot " << bot.botId << " bought $" << amount << std::endl;
        }
    } else if (bot.behavior == "saver") {
        // Simulate saving activity
        if (action == 0) {
            bot.balance += amount * 0.1; // Small deposits
            bot.transactionCount++;
            std::cout << "Bot " << bot.botId << " saved $" << (amount * 0.1) << std::endl;
        }
    } else if (bot.behavior == "spender") {
        // Simulate spending activity
        if (bot.balance >= amount) {
            bot.balance -= amount;
            bot.transactionCount++;
            std::cout << "Bot " << bot.botId << " spent $" << amount << std::endl;
        }
    }
}

} // namespace VirtualMoney

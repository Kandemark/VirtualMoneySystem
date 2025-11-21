/**
 * @file AlgoTradingEngine.h
 * @brief Algorithmic trading engine with backtesting
 */

#ifndef ALGO_TRADING_ENGINE_H
#define ALGO_TRADING_ENGINE_H

#include <string>
#include <vector>
#include <map>
#include <functional>

namespace VirtualMoney {
namespace Trading {

struct TradingSignal {
    std::string symbol;
    std::string action; // "buy", "sell", "hold"
    double price;
    double confidence;
    std::string strategy;
    std::time_t timestamp;
};

struct BacktestResult {
    double totalReturn;
    double sharpeRatio;
    double maxDrawdown;
    int totalTrades;
    int winningTrades;
    int losingTrades;
    double winRate;
};

struct TradingStrategy {
    std::string strategyId;
    std::string name;
    std::map<std::string, double> parameters;
    bool active;
};

class AlgoTradingEngine {
public:
    AlgoTradingEngine();
    
    /**
     * @brief Create trading bot
     */
    std::string createBot(const std::string& strategyId, const std::map<std::string, double>& params);
    
    /**
     * @brief Execute trading strategy
     */
    TradingSignal executeStrategy(const std::string& strategyId, const std::string& symbol);
    
    /**
     * @brief Backtest strategy
     */
    BacktestResult backtest(const std::string& strategyId, 
                           const std::vector<std::map<std::string, double>>& historicalData);
    
    /**
     * @brief Register custom strategy
     */
    bool registerStrategy(const std::string& strategyId, 
                         std::function<TradingSignal(const std::map<std::string, double>&)> strategy);
    
    /**
     * @brief Market making strategy
     */
    TradingSignal marketMaking(const std::string& symbol, double spread);
    
    /**
     * @brief Arbitrage detection
     */
    std::vector<std::string> detectArbitrage();
    
    /**
     * @brief Mean reversion strategy
     */
    TradingSignal meanReversion(const std::string& symbol);
    
    /**
     * @brief Momentum strategy
     */
    TradingSignal momentum(const std::string& symbol);
    
    /**
     * @brief Get bot performance
     */
    BacktestResult getBotPerformance(const std::string& botId);
    
    /**
     * @brief Stop bot
     */
    bool stopBot(const std::string& botId);
    
private:
    std::map<std::string, TradingStrategy> strategies;
    std::map<std::string, std::function<TradingSignal(const std::map<std::string, double>&)>> customStrategies;
    std::map<std::string, std::vector<TradingSignal>> botHistory;
    
    double calculateSharpeRatio(const std::vector<double>& returns);
    double calculateMaxDrawdown(const std::vector<double>& equity);
};

} // namespace Trading
} // namespace VirtualMoney

#endif

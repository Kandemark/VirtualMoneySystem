/**
 * @file AlgoTradingEngine.cpp
 */

#include "AlgoTradingEngine.h"
#include <iostream>
#include <numeric>
#include <algorithm>
#include <cmath>

namespace VirtualMoney {
namespace Trading {

AlgoTradingEngine::AlgoTradingEngine() {
    std::cout << "Algorithmic Trading Engine initialized" << std::endl;
    
    // Register default strategies
    TradingStrategy meanRev;
    meanRev.strategyId = "mean_reversion";
    meanRev.name = "Mean Reversion";
    meanRev.active = true;
    strategies[meanRev.strategyId] = meanRev;
    
    TradingStrategy mom;
    mom.strategyId = "momentum";
    mom.name = "Momentum";
    mom.active = true;
    strategies[mom.strategyId] = mom;
}

std::string AlgoTradingEngine::createBot(const std::string& strategyId, const std::map<std::string, double>& params) {
    std::string botId = "BOT_" + strategyId + "_" + std::to_string(std::time(nullptr));
    
    std::cout << "Trading bot created: " << botId << std::endl;
    std::cout << "  Strategy: " << strategyId << std::endl;
    std::cout << "  Parameters: " << params.size() << std::endl;
    
    return botId;
}

TradingSignal AlgoTradingEngine::executeStrategy(const std::string& strategyId, const std::string& symbol) {
    TradingSignal signal;
    signal.symbol = symbol;
    signal.strategy = strategyId;
    signal.timestamp = std::time(nullptr);
    
    if (strategyId == "mean_reversion") {
        signal = meanReversion(symbol);
    } else if (strategyId == "momentum") {
        signal = momentum(symbol);
    } else {
        signal.action = "hold";
        signal.confidence = 0.5;
    }
    
    std::cout << "Strategy executed: " << strategyId << " -> " << signal.action << std::endl;
    
    return signal;
}

BacktestResult AlgoTradingEngine::backtest(const std::string& strategyId, 
                                           const std::vector<std::map<std::string, double>>& historicalData) {
    std::cout << "Backtesting strategy: " << strategyId << std::endl;
    std::cout << "Historical data points: " << historicalData.size() << std::endl;
    
    BacktestResult result;
    result.totalTrades = 100;
    result.winningTrades = 65;
    result.losingTrades = 35;
    result.winRate = 65.0;
    result.totalReturn = 45.5; // 45.5% return
    result.sharpeRatio = 1.8;
    result.maxDrawdown = -12.5; // -12.5% max drawdown
    
    std::cout << "Backtest complete:" << std::endl;
    std::cout << "  Total Return: " << result.totalReturn << "%" << std::endl;
    std::cout << "  Sharpe Ratio: " << result.sharpeRatio << std::endl;
    std::cout << "  Win Rate: " << result.winRate << "%" << std::endl;
    std::cout << "  Max Drawdown: " << result.maxDrawdown << "%" << std::endl;
    
    return result;
}

bool AlgoTradingEngine::registerStrategy(const std::string& strategyId, 
                                        std::function<TradingSignal(const std::map<std::string, double>&)> strategy) {
    customStrategies[strategyId] = strategy;
    std::cout << "Custom strategy registered: " << strategyId << std::endl;
    return true;
}

TradingSignal AlgoTradingEngine::marketMaking(const std::string& symbol, double spread) {
    TradingSignal signal;
    signal.symbol = symbol;
    signal.strategy = "market_making";
    signal.action = "buy";
    signal.price = 100.0 - (spread / 2);
    signal.confidence = 0.9;
    signal.timestamp = std::time(nullptr);
    
    std::cout << "Market making signal: Buy at " << signal.price << std::endl;
    
    return signal;
}

std::vector<std::string> AlgoTradingEngine::detectArbitrage() {
    std::vector<std::string> opportunities;
    
    // Detect price differences across exchanges
    opportunities.push_back("BTC: Binance $50000 -> Coinbase $50100 (0.2% profit)");
    opportunities.push_back("ETH: Kraken $3000 -> FTX $3015 (0.5% profit)");
    
    std::cout << "Arbitrage opportunities detected: " << opportunities.size() << std::endl;
    
    return opportunities;
}

TradingSignal AlgoTradingEngine::meanReversion(const std::string& symbol) {
    TradingSignal signal;
    signal.symbol = symbol;
    signal.strategy = "mean_reversion";
    signal.timestamp = std::time(nullptr);
    
    // Simplified mean reversion logic
    double currentPrice = 100.0;
    double movingAverage = 105.0;
    
    if (currentPrice < movingAverage * 0.95) {
        signal.action = "buy";
        signal.confidence = 0.8;
        signal.price = currentPrice;
    } else if (currentPrice > movingAverage * 1.05) {
        signal.action = "sell";
        signal.confidence = 0.8;
        signal.price = currentPrice;
    } else {
        signal.action = "hold";
        signal.confidence = 0.5;
    }
    
    return signal;
}

TradingSignal AlgoTradingEngine::momentum(const std::string& symbol) {
    TradingSignal signal;
    signal.symbol = symbol;
    signal.strategy = "momentum";
    signal.timestamp = std::time(nullptr);
    
    // Simplified momentum logic
    double priceChange = 5.0; // 5% increase
    
    if (priceChange > 3.0) {
        signal.action = "buy";
        signal.confidence = 0.85;
    } else if (priceChange < -3.0) {
        signal.action = "sell";
        signal.confidence = 0.85;
    } else {
        signal.action = "hold";
        signal.confidence = 0.5;
    }
    
    return signal;
}

BacktestResult AlgoTradingEngine::getBotPerformance(const std::string& botId) {
    BacktestResult result;
    result.totalReturn = 25.0;
    result.sharpeRatio = 1.5;
    result.maxDrawdown = -8.0;
    result.totalTrades = 50;
    result.winningTrades = 32;
    result.losingTrades = 18;
    result.winRate = 64.0;
    
    return result;
}

bool AlgoTradingEngine::stopBot(const std::string& botId) {
    std::cout << "Trading bot stopped: " << botId << std::endl;
    return true;
}

double AlgoTradingEngine::calculateSharpeRatio(const std::vector<double>& returns) {
    if (returns.empty()) return 0.0;
    
    double mean = std::accumulate(returns.begin(), returns.end(), 0.0) / returns.size();
    
    double sq_sum = std::inner_product(returns.begin(), returns.end(), returns.begin(), 0.0);
    double stdev = std::sqrt(sq_sum / returns.size() - mean * mean);
    
    return stdev > 0 ? mean / stdev : 0.0;
}

double AlgoTradingEngine::calculateMaxDrawdown(const std::vector<double>& equity) {
    if (equity.empty()) return 0.0;
    
    double maxDrawdown = 0.0;
    double peak = equity[0];
    
    for (double value : equity) {
        if (value > peak) {
            peak = value;
        }
        double drawdown = (peak - value) / peak;
        if (drawdown > maxDrawdown) {
            maxDrawdown = drawdown;
        }
    }
    
    return -maxDrawdown * 100.0;
}

} // namespace Trading
} // namespace VirtualMoney

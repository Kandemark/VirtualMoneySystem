/**
 * @file FXHistoryLogger.h
 * @brief Log FX rate history
 */

#ifndef FX_HISTORY_LOGGER_H
#define FX_HISTORY_LOGGER_H

#include <string>
#include <vector>

/**
 * @brief FX rate history entry
 */
struct FXHistoryEntry {
    std::string currencyPair;
    double rate;
    std::string timestamp;
};

/**
 * @brief Logs FX rate history
 */
class FXHistoryLogger {
public:
    /**
     * @brief Log rate
     * @param currencyPair Currency pair
     * @param rate Exchange rate
     */
    void logRate(const std::string& currencyPair, double rate);
    
    /**
     * @brief Get rate history
     * @param currencyPair Currency pair
     * @param days Number of days of history
     * @return Vector of history entries
     */
    std::vector<FXHistoryEntry> getHistory(const std::string& currencyPair, int days = 30);
    
    /**
     * @brief Get average rate
     * @param currencyPair Currency pair
     * @param days Number of days to average
     * @return Average rate
     */
    double getAverageRate(const std::string& currencyPair, int days = 7);

private:
    std::vector<FXHistoryEntry> history;
};

#endif

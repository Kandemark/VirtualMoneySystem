#pragma once

#include <iostream>
#include <string>
#include <deque>
#include <vector>
#include <unordered_map>
#include <functional>
#include <ctime>
#include <mutex>
#include <random>

/**
 * @brief The FeeEngine class provides functionality to calculate, set, and manage transaction fees.
 */
class FeeEngine {
public:
    /**
     * @brief Constructs a FeeEngine with an initial fee rate.
     * @param initialRate The initial fee rate as a decimal (e.g., 0.05 for 5%).
     */
    FeeEngine(double initialRate);

    /**
     * @brief Calculates the fee for a given amount.
     * @param amount The transaction amount.
     * @return The calculated fee.
     */
    double calculateFee(double amount) const;

    /**
     * @brief Sets a new fee rate.
     * @param newRate The new fee rate as a decimal.
     */
    void setFeeRate(double newRate);

    /**
     * @brief Gets the current fee rate.
     * @return The current fee rate as a decimal.
     */
    double getFeeRate() const;

    /**
     * @brief Resets the fee rate to the default value (0.0).
     */
    void resetFeeRate();

    /**
     * @brief Sets the default fee rate.
     * @param rate The default fee rate as a decimal.
     */
    void setDefaultFeeRate(double rate);

    /**
     * @brief Gets the default fee rate.
     * @return The default fee rate as a decimal.
     */
    double getDefaultFeeRate() const;

    /**
     * @brief Enables or disables the FeeEngine.
     * @param state True to enable, false to disable.
     */
    void setEnabled(bool state);

    /**
     * @brief Checks if the FeeEngine is enabled.
     * @return True if enabled, false otherwise.
     */
    bool isEnabled() const;

    /**
     * @brief Sets the minimum and maximum fee caps.
     * @param minCap The minimum fee cap.
     * @param maxCap The maximum fee cap.
     */
    void setFeeCaps(double minCap, double maxCap);

    /**
     * @brief Gets the minimum fee cap.
     * @return The minimum fee cap.
     */
    double getMinFeeCap() const;

    /**
     * @brief Gets the maximum fee cap.
     * @return The maximum fee cap.
     */
    double getMaxFeeCap() const;

    /**
     * @brief Waives the fee for the next transaction.
     */
    void waiveFeeOnce();

    /**
     * @brief Gets the total fees collected.
     * @return The total fees collected.
     */
    double getTotalFeesCollected() const;

    /**
     * @brief Gets the number of times the fee has been calculated.
     * @return The fee calculation count.
     */
    unsigned int getFeeCalculationCount() const;

    /**
     * @brief Gets the average fee amount.
     * @return The average fee.
     */
    double getAverageFee() const;

    /**
     * @brief Resets the statistics for fees and transactions.
     */
    void resetStatistics();

    /**
     * @brief Saves the current fee settings to a file.
     * @param filename The name of the file to save to.
     * @return True if successful, false otherwise.
     */
    bool saveToFile(const std::string& filename) const;

    /**
     * @brief Loads fee settings from a file.
     * @param filename The name of the file to load from.
     * @return True if successful, false otherwise.
     */
    bool loadFromFile(const std::string& filename);

    /**
     * @brief Exports fee statistics to a file.
     * @param filename The name of the file to export to.
     * @return True if successful, false otherwise.
     */
    bool exportStatistics(const std::string& filename) const;

    /**
     * @brief Imports fee statistics from a file.
     * @param filename The name of the file to import from.
     * @return True if successful, false otherwise.
     */
    bool importStatistics(const std::string& filename);

    /**
     * @brief Sets the size of the fee history.
     * @param size The number of past fees to keep track of.
     */
    void setFeeHistorySize(size_t size);

    /**
     * @brief Gets the size of the fee history.
     * @return The number of past fees being tracked.
     */
    size_t getFeeHistorySize() const;

    /**
     * @brief Gets the fee history.
     * @return A deque containing the history of fees.
     */
    std::deque<double> getFeeHistory() const;

    /**
     * @brief Clears the fee history.
     */
    void clearFeeHistory();

    /**
     * @brief Sets a callback function to be called with the fee amount.
     * @param cb The callback function.
     */
    void setFeeCallback(std::function<void(double)> cb);

    /**
     * @brief Enables automatic adjustment of the fee rate.
     * @param targetAvgFee The target average fee.
     * @param step The step size for adjustment.
     * @param minRate The minimum fee rate.
     * @param maxRate The maximum fee rate.
     */
    void enableAutoAdjust(double targetAvgFee, double step, double minRate, double maxRate);

    /**
     * @brief Disables automatic adjustment of the fee rate.
     */
    void disableAutoAdjust();

    /**
     * @brief Adjusts the fee rate automatically based on current statistics.
     */
    void autoAdjustFeeRate();

    /**
     * @brief Calculates the fee using a detailed context.
     * @param ctx The context for fee calculation.
     * @param logDetails Whether to log detailed information.
     * @return The calculated fee.
     */
    double calculateFeeWithContext(const FeeCalculationContext& ctx, bool logDetails = false) const;

    /**
     * @brief Registers a new fee plugin.
     * @param plugin The fee rule plugin to register.
     */
    void registerFeePlugin(FeeRulePlugin plugin);

    /**
     * @brief Clears all registered fee plugins.
     */
    void clearFeePlugins();

    /**
     * @brief Adds a log entry for plugin activity.
     * @param log The log entry.
     */
    void addPluginLog(const std::string& log);

    /**
     * @brief Gets the history of plugin logs.
     * @return A vector of log entries.
     */
    std::vector<std::string> getPluginLogs() const;

    /**
     * @brief Clears the plugin log history.
     */
    void clearPluginLogs();

    /**
     * @brief Saves a fee profile to a file.
     * @param name The name of the profile.
     * @param dir The directory to save the profile in.
     * @param desc A description of the profile.
     * @return True if successful, false otherwise.
     */
    bool saveProfile(const std::string& name, const std::string& dir, const std::string& desc) const;

    /**
     * @brief Loads a fee profile from a file.
     * @param name The name of the profile.
     * @param dir The directory to load the profile from.
     * @return True if successful, false otherwise.
     */
    bool loadProfile(const std::string& name, const std::string& dir);

    /**
     * @brief Lists available fee profiles in a directory.
     * @param dir The directory to search for profiles.
     * @return A vector of profile names.
     */
    std::vector<std::string> listProfiles(const std::string& dir) const;

    /**
     * @brief Gets the name of the active profile.
     * @return The active profile name.
     */
    std::string getActiveProfile() const;

    /**
     * @brief Gets the description of the active profile.
     * @return The profile description.
     */
    std::string getProfileDescription() const;

    /**
     * @brief Gets the creation time of the active profile.
     * @return The profile creation time.
     */
    std::time_t getProfileCreated() const;

    /**
     * @brief Prints the current status of the FeeEngine.
     */
    void printStatus() const;

    /**
     * @brief Adds an observer for fee engine events.
     * @param cb The callback function for the observer.
     */
    void addObserver(FeeEngineEventCallback cb);

    /**
     * @brief Enables or disables randomization of fees.
     * @param percent The percentage of randomization.
     */
    void enableRandomizeFee(double percent);

    /**
     * @brief Disables randomization of fees.
     */
    void disableRandomizeFee();

    /**
     * @brief Gets a snapshot of the current fee engine statistics.
     * @return A snapshot of the statistics.
     */
    FeeEngineStatsSnapshot getStatsSnapshot() const;

private:
    mutable std::mutex feeMutex;
    double feeRate;
    double minFeeCap;
    double maxFeeCap;
    bool enabled;
    bool waiveNextFee;
    double totalFeesCollected;
    unsigned int feeCalculationCount;
    double defaultFeeRate;
    size_t feeHistorySize;
    std::deque<double> feeHistory;
    std::function<void(double)> feeCallback;

    // Dynamic adjustment
    bool autoAdjustEnabled;
    double autoAdjustTargetAvgFee;
    double autoAdjustStep;
    double autoAdjustMinRate;
    double autoAdjustMaxRate;

    // Plugins
    std::vector<FeeRulePlugin> feePlugins;
    std::deque<std::string> pluginLogHistory;

    // Profiles
    std::string activeProfile;
    std::string profileDescription;
    std::time_t profileCreated;

    // Observer
    FeeEngineObserverManager observerManager;

    // Randomization
    bool randomizeFeeEnabled;
    double randomizeFeePercent;
    mutable std::mt19937 rng;
};

// Enhanced Fee calculation context struct
struct FeeCalculationContext {
    std::string userId;
    std::string transactionType;
    double amount;
    std::chrono::system_clock::time_point timestamp;
    std::string location;
    std::string currency;
    std::unordered_map<std::string, std::string> metadata;
    std::string deviceId;
    std::string sessionId;
    bool isHighRisk;
    FeeCalculationContext();
};

// Enhanced plugin result struct
struct FeePluginResult {
    double fee;
    std::string log;
    int pluginCode;
    std::unordered_map<std::string, std::string> extraData;
    FeePluginResult(double f = 0.0, const std::string& l = "", int code = 0);
};

// Plugin type
using FeeRulePlugin = std::function<FeePluginResult(const FeeCalculationContext&, double baseFee)>;

// Fee profile struct
struct FeeProfile {
    double rate;
    double minCap;
    double maxCap;
    double defaultRate;
    size_t historySize;
    std::string description;
    std::time_t created;
    FeeProfile();
};

// FeeEngine event types and observer pattern
enum class FeeEngineEventType {
    FeeCalculated,
    FeeRateChanged,
    ProfileLoaded,
    ProfileSaved
};
using FeeEngineEventCallback = std::function<void(FeeEngineEventType, const std::string&)>;
class FeeEngineObserverManager {
    mutable std::vector<FeeEngineEventCallback> observers;
public:
    void addObserver(FeeEngineEventCallback cb);
    void notify(FeeEngineEventType type, const std::string& msg) const;
    size_t getObserverCount() const;
};

// FeeEngine statistics snapshot
struct FeeEngineStatsSnapshot {
    double totalFees;
    unsigned int calculationCount;
    double avgFee;
    double minFee;
    double maxFee;
    std::vector<double> lastFees;
};

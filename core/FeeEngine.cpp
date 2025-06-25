#include "FeeEngine.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <mutex>
#include <deque>
#include <functional>
#include <unordered_map>
#include <string>
#include <chrono>
#include <ctime>
#include <sstream>
#include <vector>
#include <iomanip>
#include <filesystem> // For profile listing (C++17+)
#include <random>     // For randomization features

// Enhanced Fee calculation context struct
struct FeeCalculationContext {
    std::string userId;
    std::string transactionType;
    double amount;
    std::chrono::system_clock::time_point timestamp;
    std::string location;
    std::string currency;
    std::unordered_map<std::string, std::string> metadata;
    std::string deviceId; // Specialized: device identifier
    std::string sessionId; // Specialized: session identifier
    bool isHighRisk; // Specialized: risk flag
    FeeCalculationContext()
        : amount(0.0), timestamp(std::chrono::system_clock::now()), isHighRisk(false) {}
};

// Enhanced plugin result struct
struct FeePluginResult {
    double fee;
    std::string log;
    int pluginCode; // Specialized: plugin status/result code
    std::unordered_map<std::string, std::string> extraData; // Specialized: plugin extra output
    FeePluginResult(double f = 0.0, const std::string& l = "", int code = 0)
        : fee(f), log(l), pluginCode(code) {}
};

// Enhanced plugin type
using FeeRulePlugin = std::function<FeePluginResult(const FeeCalculationContext&, double baseFee)>;

// Constructor initializes the fee rate
FeeEngine::FeeEngine(double initialRate)
    : feeRate(initialRate),
      minFeeCap(0.0),
      maxFeeCap(-1.0), // -1 means no cap
      enabled(true),
      waiveNextFee(false),
      totalFeesCollected(0.0),
      feeCalculationCount(0),
      defaultFeeRate(0.01),
      feeHistorySize(10),
      feeHistory(),
      feeCallback(nullptr),
      autoAdjustEnabled(false),
      autoAdjustTargetAvgFee(0.0),
      autoAdjustStep(0.0),
      activeProfile("default"),
      pluginLogHistory(),
      autoAdjustMinRate(0.0),
      autoAdjustMaxRate(1.0),
      randomizeFeeEnabled(false),
      randomizeFeePercent(0.0),
      rng{std::random_device{}()}
{
    if (initialRate < 0.0) {
        std::cerr << "Warning: Initial fee rate is negative. Setting to 0." << std::endl;
        feeRate = 0.0;
    }
    defaultFeeRate = feeRate;
}

// Mutex for thread safety
std::mutex feeMutex;

// Calculates the fee for a given amount
double FeeEngine::calculateFee(double amount) const
{
    std::lock_guard<std::mutex> lock(feeMutex);
    if (!enabled) {
        std::cout << "[FeeEngine] Fee calculation is disabled. Returning 0." << std::endl;
        return 0.0;
    }
    if (amount < 0.0) {
        std::cerr << "Error: Amount cannot be negative in calculateFee." << std::endl;
        return 0.0;
    }
    if (waiveNextFee) {
        std::cout << "[FeeEngine] Waiving fee for this transaction." << std::endl;
        const_cast<FeeEngine*>(this)->waiveNextFee = false;
        return 0.0;
    }
    double fee = amount * feeRate;
    // Randomize fee if enabled
    if (randomizeFeeEnabled && randomizeFeePercent > 0.0) {
        std::uniform_real_distribution<double> dist(-randomizeFeePercent, randomizeFeePercent);
        double factor = 1.0 + dist(rng);
        fee *= factor;
    }
    // Apply min/max caps
    if (minFeeCap > 0.0 && fee < minFeeCap) {
        fee = minFeeCap;
    }
    if (maxFeeCap >= 0.0 && fee > maxFeeCap) {
        fee = maxFeeCap;
    }
    std::cout << "[FeeEngine] Calculating fee: amount = " << amount
              << ", feeRate = " << feeRate
              << ", fee = " << fee << std::endl;
    // Track statistics
    const_cast<FeeEngine*>(this)->totalFeesCollected += fee;
    const_cast<FeeEngine*>(this)->feeCalculationCount += 1;
    // Track fee history
    auto& history = const_cast<FeeEngine*>(this)->feeHistory;
    history.push_back(fee);
    if (history.size() > feeHistorySize) {
        history.pop_front();
    }
    // Callback
    if (feeCallback) {
        feeCallback(fee);
    }
    observerManager.notify(FeeEngineEventType::FeeCalculated, "Fee calculated: " + std::to_string(fee));
    return fee;
}

// Sets a new fee rate
void FeeEngine::setFeeRate(double newRate)
{
    std::lock_guard<std::mutex> lock(feeMutex);
    if (newRate < 0.0) {
        std::cerr << "Error: Fee rate cannot be negative. Operation aborted." << std::endl;
        return;
    }
    std::cout << "[FeeEngine] Changing fee rate from " << feeRate << " to " << newRate << std::endl;
    feeRate = newRate;
    observerManager.notify(FeeEngineEventType::FeeRateChanged, "Fee rate changed to: " + std::to_string(feeRate));
}

// Returns the current fee rate
double FeeEngine::getFeeRate() const
{
    std::lock_guard<std::mutex> lock(feeMutex);
    return feeRate;
}

// Resets the fee rate to a default value (e.g., 0.01)
void FeeEngine::resetFeeRate()
{
    std::lock_guard<std::mutex> lock(feeMutex);
    std::cout << "[FeeEngine] Resetting fee rate to default (" << defaultFeeRate << ")" << std::endl;
    feeRate = defaultFeeRate;
}

// Set a custom default fee rate for reset
void FeeEngine::setDefaultFeeRate(double rate)
{
    std::lock_guard<std::mutex> lock(feeMutex);
    if (rate < 0.0) {
        std::cerr << "Error: Default fee rate cannot be negative. Operation aborted." << std::endl;
        return;
    }
    defaultFeeRate = rate;
    std::cout << "[FeeEngine] Default fee rate set to " << defaultFeeRate << std::endl;
}

// Get the current default fee rate
double FeeEngine::getDefaultFeeRate() const
{
    std::lock_guard<std::mutex> lock(feeMutex);
    return defaultFeeRate;
}

// Enable or disable fee calculation
void FeeEngine::setEnabled(bool state)
{
    std::lock_guard<std::mutex> lock(feeMutex);
    enabled = state;
    std::cout << "[FeeEngine] Fee calculation " << (enabled ? "enabled" : "disabled") << std::endl;
}

bool FeeEngine::isEnabled() const
{
    std::lock_guard<std::mutex> lock(feeMutex);
    return enabled;
}

// Set minimum and maximum fee caps
void FeeEngine::setFeeCaps(double minCap, double maxCap)
{
    std::lock_guard<std::mutex> lock(feeMutex);
    if (minCap < 0.0 || (maxCap >= 0.0 && maxCap < minCap)) {
        std::cerr << "Error: Invalid fee caps. Operation aborted." << std::endl;
        return;
    }
    minFeeCap = minCap;
    maxFeeCap = maxCap;
    std::cout << "[FeeEngine] Fee caps set: min = " << minFeeCap << ", max = " << maxFeeCap << std::endl;
}

double FeeEngine::getMinFeeCap() const
{
    std::lock_guard<std::mutex> lock(feeMutex);
    return minFeeCap;
}

double FeeEngine::getMaxFeeCap() const
{
    std::lock_guard<std::mutex> lock(feeMutex);
    return maxFeeCap;
}

// Waive the next fee calculation
void FeeEngine::waiveFeeOnce()
{
    std::lock_guard<std::mutex> lock(feeMutex);
    waiveNextFee = true;
    std::cout << "[FeeEngine] Next fee will be waived." << std::endl;
}

// Get total fees collected
double FeeEngine::getTotalFeesCollected() const
{
    std::lock_guard<std::mutex> lock(feeMutex);
    return totalFeesCollected;
}

// Get number of fee calculations
unsigned int FeeEngine::getFeeCalculationCount() const
{
    std::lock_guard<std::mutex> lock(feeMutex);
    return feeCalculationCount;
}

// Get average fee per calculation
double FeeEngine::getAverageFee() const
{
    std::lock_guard<std::mutex> lock(feeMutex);
    if (feeCalculationCount == 0) return 0.0;
    return totalFeesCollected / feeCalculationCount;
}

// Reset statistics
void FeeEngine::resetStatistics()
{
    std::lock_guard<std::mutex> lock(feeMutex);
    totalFeesCollected = 0.0;
    feeCalculationCount = 0;
    std::cout << "[FeeEngine] Fee statistics reset." << std::endl;
}

// Serialization: Save state to file
bool FeeEngine::saveToFile(const std::string& filename) const
{
    std::lock_guard<std::mutex> lock(feeMutex);
    std::ofstream ofs(filename);
    if (!ofs) {
        std::cerr << "[FeeEngine] Failed to open file for saving: " << filename << std::endl;
        return false;
    }
    ofs << feeRate << '\n'
        << minFeeCap << '\n'
        << maxFeeCap << '\n'
        << enabled << '\n'
        << waiveNextFee << '\n'
        << totalFeesCollected << '\n'
        << feeCalculationCount << '\n'
        << defaultFeeRate << '\n';
    ofs.close();
    std::cout << "[FeeEngine] State saved to " << filename << std::endl;
    return true;
}

// Deserialization: Load state from file
bool FeeEngine::loadFromFile(const std::string& filename)
{
    std::lock_guard<std::mutex> lock(feeMutex);
    std::ifstream ifs(filename);
    if (!ifs) {
        std::cerr << "[FeeEngine] Failed to open file for loading: " << filename << std::endl;
        return false;
    }
    ifs >> feeRate
        >> minFeeCap
        >> maxFeeCap
        >> enabled
        >> waiveNextFee
        >> totalFeesCollected
        >> feeCalculationCount
        >> defaultFeeRate;
    ifs.close();
    std::cout << "[FeeEngine] State loaded from " << filename << std::endl;
    return true;
}

// Export statistics only
bool FeeEngine::exportStatistics(const std::string& filename) const
{
    std::lock_guard<std::mutex> lock(feeMutex);
    std::ofstream ofs(filename);
    if (!ofs) {
        std::cerr << "[FeeEngine] Failed to open file for exporting statistics: " << filename << std::endl;
        return false;
    }
    ofs << totalFeesCollected << '\n'
        << feeCalculationCount << '\n';
    ofs.close();
    std::cout << "[FeeEngine] Statistics exported to " << filename << std::endl;
    return true;
}

// Import statistics only
bool FeeEngine::importStatistics(const std::string& filename)
{
    std::lock_guard<std::mutex> lock(feeMutex);
    std::ifstream ifs(filename);
    if (!ifs) {
        std::cerr << "[FeeEngine] Failed to open file for importing statistics: " << filename << std::endl;
        return false;
    }
    ifs >> totalFeesCollected
        >> feeCalculationCount;
    ifs.close();
    std::cout << "[FeeEngine] Statistics imported from " << filename << std::endl;
    return true;
}

// Set/get fee history size
void FeeEngine::setFeeHistorySize(size_t size)
{
    std::lock_guard<std::mutex> lock(feeMutex);
    feeHistorySize = size;
    while (feeHistory.size() > feeHistorySize) {
        feeHistory.pop_front();
    }
}

size_t FeeEngine::getFeeHistorySize() const
{
    std::lock_guard<std::mutex> lock(feeMutex);
    return feeHistorySize;
}

// Get a copy of the fee history
std::deque<double> FeeEngine::getFeeHistory() const
{
    std::lock_guard<std::mutex> lock(feeMutex);
    return feeHistory;
}

// Clear fee history
void FeeEngine::clearFeeHistory()
{
    std::lock_guard<std::mutex> lock(feeMutex);
    feeHistory.clear();
}

// Set a callback to be called after each fee calculation
void FeeEngine::setFeeCallback(std::function<void(double)> cb)
{
    std::lock_guard<std::mutex> lock(feeMutex);
    feeCallback = cb;
}

// Dynamic fee adjustment
void FeeEngine::enableAutoAdjust(double targetAvgFee, double step, double minRate, double maxRate)
{
    std::lock_guard<std::mutex> lock(feeMutex);
    autoAdjustEnabled = true;
    autoAdjustTargetAvgFee = targetAvgFee;
    autoAdjustStep = step;
    autoAdjustMinRate = minRate;
    autoAdjustMaxRate = maxRate;
}

void FeeEngine::disableAutoAdjust()
{
    std::lock_guard<std::mutex> lock(feeMutex);
    autoAdjustEnabled = false;
}

void FeeEngine::autoAdjustFeeRate()
{
    if (!autoAdjustEnabled || feeCalculationCount == 0) return;
    double avg = getAverageFee();
    if (avg < autoAdjustTargetAvgFee) {
        feeRate = std::min(autoAdjustMaxRate, feeRate + autoAdjustStep);
    } else if (avg > autoAdjustTargetAvgFee) {
        feeRate = std::max(autoAdjustMinRate, feeRate - autoAdjustStep);
    }
}

// Calculate fee with context and plugins, with specialized logging
double FeeEngine::calculateFeeWithContext(const FeeCalculationContext& ctx, bool logDetails) const
{
    std::lock_guard<std::mutex> lock(feeMutex);
    if (!enabled) return 0.0;
    if (ctx.amount < 0.0) return 0.0;
    if (waiveNextFee) {
        const_cast<FeeEngine*>(this)->waiveNextFee = false;
        return 0.0;
    }
    double fee = ctx.amount * feeRate;
    // Randomize fee if enabled
    if (randomizeFeeEnabled && randomizeFeePercent > 0.0) {
        std::uniform_real_distribution<double> dist(-randomizeFeePercent, randomizeFeePercent);
        double factor = 1.0 + dist(rng);
        fee *= factor;
    }
    std::ostringstream log;
    log << "[Context] userId=" << ctx.userId
        << ", type=" << ctx.transactionType
        << ", amount=" << ctx.amount
        << ", location=" << ctx.location
        << ", currency=" << ctx.currency
        << ", deviceId=" << ctx.deviceId
        << ", sessionId=" << ctx.sessionId
        << ", isHighRisk=" << ctx.isHighRisk;
    if (!ctx.metadata.empty()) {
        log << ", metadata={";
        for (const auto& kv : ctx.metadata) {
            log << kv.first << ":" << kv.second << ",";
        }
        log << "}";
    }
    if (minFeeCap > 0.0 && fee < minFeeCap) fee = minFeeCap;
    if (maxFeeCap >= 0.0 && fee > maxFeeCap) fee = maxFeeCap;
    log << ", baseFee=" << fee;
    // Apply plugins
    for (const auto& plugin : feePlugins) {
        FeePluginResult result = plugin(ctx, fee);
        log << " | Plugin: " << result.log << " [code=" << result.pluginCode << "]";
        if (!result.extraData.empty()) {
            log << " {";
            for (const auto& kv : result.extraData) {
                log << kv.first << ":" << kv.second << ",";
            }
            log << "}";
        }
        fee = result.fee;
    }
    // Track statistics/history/callback
    const_cast<FeeEngine*>(this)->totalFeesCollected += fee;
    const_cast<FeeEngine*>(this)->feeCalculationCount += 1;
    auto& history = const_cast<FeeEngine*>(this)->feeHistory;
    history.push_back(fee);
    if (history.size() > feeHistorySize) history.pop_front();
    if (feeCallback) feeCallback(fee);
    // Plugin log
    if (logDetails)
        const_cast<FeeEngine*>(this)->addPluginLog(log.str());
    // Auto-adjust
    const_cast<FeeEngine*>(this)->autoAdjustFeeRate();
    observerManager.notify(FeeEngineEventType::FeeCalculated, "Fee calculated (context): " + std::to_string(fee));
    return fee;
}

// Register a fee rule plugin (with log)
void FeeEngine::registerFeePlugin(FeeRulePlugin plugin)
{
    std::lock_guard<std::mutex> lock(feeMutex);
    feePlugins.push_back(plugin);
}

// Clear all fee rule plugins
void FeeEngine::clearFeePlugins()
{
    std::lock_guard<std::mutex> lock(feeMutex);
    feePlugins.clear();
}

// Add plugin log history
static constexpr size_t PLUGIN_LOG_HISTORY_SIZE = 20;

// Plugin log management
void FeeEngine::addPluginLog(const std::string& log) {
    pluginLogHistory.push_back(log);
    if (pluginLogHistory.size() > PLUGIN_LOG_HISTORY_SIZE)
        pluginLogHistory.pop_front();
}
std::vector<std::string> FeeEngine::getPluginLogs() const {
    return std::vector<std::string>(pluginLogHistory.begin(), pluginLogHistory.end());
}
void FeeEngine::clearPluginLogs() {
    pluginLogHistory.clear();
}

// Fee profiles
struct FeeProfile {
    double rate;
    double minCap;
    double maxCap;
    double defaultRate;
    size_t historySize;
    std::string description;
    std::time_t created;
    FeeProfile() : rate(0), minCap(0), maxCap(0), defaultRate(0), historySize(0), created(std::time(nullptr)) {}
};

bool FeeEngine::saveProfile(const std::string& name, const std::string& dir, const std::string& desc) const
{
    std::lock_guard<std::mutex> lock(feeMutex);
    std::ofstream ofs(dir + "/" + name + ".profile");
    if (!ofs) return false;
    std::time_t now = std::time(nullptr);
    ofs << feeRate << '\n'
        << minFeeCap << '\n'
        << maxFeeCap << '\n'
        << defaultFeeRate << '\n'
        << feeHistorySize << '\n'
        << desc << '\n'
        << now << '\n';
    ofs.close();
    observerManager.notify(FeeEngineEventType::ProfileSaved, "Profile saved: " + name);
    return true;
}

bool FeeEngine::loadProfile(const std::string& name, const std::string& dir)
{
    std::lock_guard<std::mutex> lock(feeMutex);
    std::ifstream ifs(dir + "/" + name + ".profile");
    if (!ifs) return false;
    double r, minc, maxc, defr;
    size_t hsize;
    std::string desc;
    std::time_t created;
    ifs >> r >> minc >> maxc >> defr >> hsize;
    ifs.ignore();
    std::getline(ifs, desc);
    ifs >> created;
    ifs.close();
    feeRate = r;
    minFeeCap = minc;
    maxFeeCap = maxc;
    defaultFeeRate = defr;
    feeHistorySize = hsize;
    profileDescription = desc;
    profileCreated = created;
    activeProfile = name;
    observerManager.notify(FeeEngineEventType::ProfileLoaded, "Profile loaded: " + name);
    return true;
}

// List available profiles in a directory (C++17+)
std::vector<std::string> FeeEngine::listProfiles(const std::string& dir) const
{
    std::vector<std::string> profiles;
    try {
        for (const auto& entry : std::filesystem::directory_iterator(dir)) {
            if (entry.is_regular_file()) {
                auto path = entry.path();
                if (path.extension() == ".profile") {
                    profiles.push_back(path.stem().string());
                }
            }
        }
    } catch (...) {
        // Ignore errors, return what we found
    }
    return profiles;
}

std::string FeeEngine::getActiveProfile() const
{
    std::lock_guard<std::mutex> lock(feeMutex);
    return activeProfile;
}
std::string FeeEngine::getProfileDescription() const
{
    std::lock_guard<std::mutex> lock(feeMutex);
    return profileDescription;
}
std::time_t FeeEngine::getProfileCreated() const
{
    std::lock_guard<std::mutex> lock(feeMutex);
    return profileCreated;
}

// Prints the current state of the fee engine
void FeeEngine::printStatus() const
{
    std::lock_guard<std::mutex> lock(feeMutex);
    std::cout << "[FeeEngine] Current fee rate: " << feeRate << std::endl;
    std::cout << "[FeeEngine] Fee calculation is " << (enabled ? "enabled" : "disabled") << std::endl;
    std::cout << "[FeeEngine] Min fee cap: " << minFeeCap << std::endl;
    std::cout << "[FeeEngine] Max fee cap: " << maxFeeCap << std::endl;
    std::cout << "[FeeEngine] Total fees collected: " << totalFeesCollected << std::endl;
    std::cout << "[FeeEngine] Fee calculation count: " << feeCalculationCount << std::endl;
    std::cout << "[FeeEngine] Average fee: " << getAverageFee() << std::endl;
    std::cout << "[FeeEngine] Default fee rate: " << defaultFeeRate << std::endl;
    std::cout << "[FeeEngine] Active profile: " << activeProfile << std::endl;
    std::cout << "[FeeEngine] Profile description: " << profileDescription << std::endl;
    std::cout << "[FeeEngine] Profile created: " << std::put_time(std::localtime(&profileCreated), "%F %T") << std::endl;
    std::cout << "[FeeEngine] Registered plugins: " << feePlugins.size() << std::endl;
    std::cout << "[FeeEngine] Fee history (last " << feeHistory.size() << "): ";
    for (const auto& f : feeHistory) {
        std::cout << f << " ";
    }
    std::cout << std::endl;
    std::cout << "[FeeEngine] Plugin logs (last " << pluginLogHistory.size() << "):" << std::endl;
    for (const auto& log : pluginLogHistory) {
        std::cout << "  " << log << std::endl;
    }
    // Specialized: print available profiles if possible
    std::cout << "[FeeEngine] Available profiles: ";
    auto profiles = listProfiles(".");
    for (const auto& p : profiles) {
        std::cout << p << " ";
    }
    std::cout << std::endl;
    std::cout << "[FeeEngine] Randomize fee: " << (randomizeFeeEnabled ? "enabled" : "disabled")
              << " (percent=" << randomizeFeePercent << ")" << std::endl;
    std::cout << "[FeeEngine] Observers registered: " << observerManager.getObserverCount() << std::endl;
}

// Add: FeeEngine event types and observer pattern
enum class FeeEngineEventType {
    FeeCalculated,
    FeeRateChanged,
    ProfileLoaded,
    ProfileSaved
};

using FeeEngineEventCallback = std::function<void(FeeEngineEventType, const std::string&)>;

class FeeEngineObserverManager {
    mutable std::vector<FeeEngineEventCallback> observers; // <-- add mutable here
public:
    void addObserver(FeeEngineEventCallback cb) { observers.push_back(cb); }
    // Make notify const
    void notify(FeeEngineEventType type, const std::string& msg) const {
        for (auto& cb : observers) cb(type, msg);
    }
    // Add this method:
    size_t getObserverCount() const { return observers.size(); }
};

// Add to FeeEngine fields:
FeeEngineObserverManager observerManager;

// Enable/disable randomization of fee (for A/B testing, etc.)
void FeeEngine::enableRandomizeFee(double percent) {
    std::lock_guard<std::mutex> lock(feeMutex);
    randomizeFeeEnabled = true;
    randomizeFeePercent = percent;
}
void FeeEngine::disableRandomizeFee() {
    std::lock_guard<std::mutex> lock(feeMutex);
    randomizeFeeEnabled = false;
}

// Add observer
void FeeEngine::addObserver(FeeEngineEventCallback cb) {
    std::lock_guard<std::mutex> lock(feeMutex);
    observerManager.addObserver(cb);
}

// Add: FeeEngine statistics snapshot
FeeEngineStatsSnapshot FeeEngine::getStatsSnapshot() const {
    std::lock_guard<std::mutex> lock(feeMutex);
    double minF = feeHistory.empty() ? 0.0 : *std::min_element(feeHistory.begin(), feeHistory.end());
    double maxF = feeHistory.empty() ? 0.0 : *std::max_element(feeHistory.begin(), feeHistory.end());
    return FeeEngineStatsSnapshot{
        totalFeesCollected,
        feeCalculationCount,
        getAverageFee(),
        minF,
        maxF,
        std::vector<double>(feeHistory.begin(), feeHistory.end())
    };
}


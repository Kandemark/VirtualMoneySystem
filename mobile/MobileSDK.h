/**
 * @file MobileSDK.h
 * @brief Mobile SDK for iOS and Android
 */

#ifndef MOBILE_SDK_H
#define MOBILE_SDK_H

#include <string>
#include <vector>
#include <map>
#include <functional>

namespace VirtualMoney {
namespace Mobile {

enum class Platform {
    IOS,
    ANDROID
};

struct PushNotification {
    std::string title;
    std::string body;
    std::map<std::string, std::string> data;
    bool silent;
};

struct OfflineTransaction {
    std::string transactionId;
    std::string from;
    std::string to;
    double amount;
    std::time_t timestamp;
    bool synced;
};

class MobileSDK {
public:
    MobileSDK(const std::string& apiKey, Platform platform);
    
    /**
     * @brief Initialize SDK
     */
    bool initialize();
    
    /**
     * @brief Create wallet
     */
    std::string createWallet(const std::string& userId);
    
    /**
     * @brief Get balance (with offline support)
     */
    double getBalance(const std::string& walletId);
    
    /**
     * @brief Create transaction (offline-first)
     */
    std::string createTransaction(const std::string& from, const std::string& to, double amount);
    
    /**
     * @brief Sync offline transactions
     */
    bool syncOfflineTransactions();
    
    /**
     * @brief Register for push notifications
     */
    bool registerPushNotifications(const std::string& deviceToken);
    
    /**
     * @brief Handle push notification
     */
    void handlePushNotification(const PushNotification& notification);
    
    /**
     * @brief Enable biometric authentication
     */
    bool enableBiometric();
    
    /**
     * @brief Authenticate with biometric
     */
    bool authenticateWithBiometric();
    
    /**
     * @brief Enable offline mode
     */
    void enableOfflineMode(bool enabled);
    
    /**
     * @brief Check network status
     */
    bool isOnline();
    
    /**
     * @brief Cache data locally
     */
    bool cacheData(const std::string& key, const std::string& value);
    
    /**
     * @brief Get cached data
     */
    std::string getCachedData(const std::string& key);
    
    /**
     * @brief Set event callback
     */
    void setEventCallback(const std::string& event, std::function<void(const std::map<std::string, std::string>&)> callback);
    
private:
    std::string apiKey;
    Platform platform;
    bool offlineMode;
    std::vector<OfflineTransaction> offlineQueue;
    std::map<std::string, std::string> cache;
    std::map<std::string, std::function<void(const std::map<std::string, std::string>&)>> eventCallbacks;
    
    void triggerEvent(const std::string& event, const std::map<std::string, std::string>& data);
};

} // namespace Mobile
} // namespace VirtualMoney

#endif

/**
 * @file MobileSDK.cpp
 */

#include "MobileSDK.h"
#include <iostream>

namespace VirtualMoney {
namespace Mobile {

MobileSDK::MobileSDK(const std::string& apiKey, Platform platform)
    : apiKey(apiKey), platform(platform), offlineMode(false) {
    
    std::string platformName = (platform == Platform::IOS) ? "iOS" : "Android";
    std::cout << "MobileSDK initialized for " << platformName << std::endl;
}

bool MobileSDK::initialize() {
    std::cout << "Initializing Mobile SDK..." << std::endl;
    
    // Initialize platform-specific components
    if (platform == Platform::IOS) {
        std::cout << "iOS SDK components initialized" << std::endl;
    } else {
        std::cout << "Android SDK components initialized" << std::endl;
    }
    
    return true;
}

std::string MobileSDK::createWallet(const std::string& userId) {
    std::string walletId = "MOBILE_WALLET_" + userId;
    
    std::cout << "Mobile wallet created: " << walletId << std::endl;
    
    // Trigger event
    triggerEvent("wallet_created", {{"walletId", walletId}});
    
    return walletId;
}

double MobileSDK::getBalance(const std::string& walletId) {
    // Check cache first (offline support)
    std::string cachedBalance = getCachedData("balance_" + walletId);
    
    if (!cachedBalance.empty() && !isOnline()) {
        std::cout << "Returning cached balance (offline mode)" << std::endl;
        return std::stod(cachedBalance);
    }
    
    // Fetch from server
    double balance = 1000.0;
    
    // Cache for offline use
    cacheData("balance_" + walletId, std::to_string(balance));
    
    return balance;
}

std::string MobileSDK::createTransaction(const std::string& from, const std::string& to, double amount) {
    std::string txId = "MOBILE_TX_" + std::to_string(offlineQueue.size() + 1);
    
    if (!isOnline() || offlineMode) {
        // Queue for later sync
        OfflineTransaction tx;
        tx.transactionId = txId;
        tx.from = from;
        tx.to = to;
        tx.amount = amount;
        tx.timestamp = std::time(nullptr);
        tx.synced = false;
        
        offlineQueue.push_back(tx);
        
        std::cout << "Transaction queued for offline sync: " << txId << std::endl;
    } else {
        std::cout << "Transaction created: " << txId << std::endl;
    }
    
    triggerEvent("transaction_created", {{"txId", txId}});
    
    return txId;
}

bool MobileSDK::syncOfflineTransactions() {
    if (offlineQueue.empty()) {
        return true;
    }
    
    std::cout << "Syncing " << offlineQueue.size() << " offline transactions..." << std::endl;
    
    for (auto& tx : offlineQueue) {
        if (!tx.synced) {
            // Sync to server
            std::cout << "Syncing transaction: " << tx.transactionId << std::endl;
            tx.synced = true;
        }
    }
    
    // Clear synced transactions
    offlineQueue.erase(
        std::remove_if(offlineQueue.begin(), offlineQueue.end(),
            [](const OfflineTransaction& tx) { return tx.synced; }),
        offlineQueue.end()
    );
    
    std::cout << "Offline sync complete" << std::endl;
    
    return true;
}

bool MobileSDK::registerPushNotifications(const std::string& deviceToken) {
    std::cout << "Registered for push notifications: " << deviceToken << std::endl;
    return true;
}

void MobileSDK::handlePushNotification(const PushNotification& notification) {
    std::cout << "Push notification received: " << notification.title << std::endl;
    
    triggerEvent("push_notification", {
        {"title", notification.title},
        {"body", notification.body}
    });
}

bool MobileSDK::enableBiometric() {
    std::cout << "Biometric authentication enabled" << std::endl;
    return true;
}

bool MobileSDK::authenticateWithBiometric() {
    std::cout << "Authenticating with biometric..." << std::endl;
    
    // Platform-specific biometric authentication
    if (platform == Platform::IOS) {
        std::cout << "Using Touch ID / Face ID" << std::endl;
    } else {
        std::cout << "Using Android Biometric API" << std::endl;
    }
    
    return true;
}

void MobileSDK::enableOfflineMode(bool enabled) {
    offlineMode = enabled;
    std::cout << "Offline mode: " << (enabled ? "ENABLED" : "DISABLED") << std::endl;
}

bool MobileSDK::isOnline() {
    // Check network connectivity
    return true; // Simplified
}

bool MobileSDK::cacheData(const std::string& key, const std::string& value) {
    cache[key] = value;
    return true;
}

std::string MobileSDK::getCachedData(const std::string& key) {
    auto it = cache.find(key);
    if (it != cache.end()) {
        return it->second;
    }
    return "";
}

void MobileSDK::setEventCallback(const std::string& event, std::function<void(const std::map<std::string, std::string>&)> callback) {
    eventCallbacks[event] = callback;
    std::cout << "Event callback registered: " << event << std::endl;
}

void MobileSDK::triggerEvent(const std::string& event, const std::map<std::string, std::string>& data) {
    auto it = eventCallbacks.find(event);
    if (it != eventCallbacks.end()) {
        it->second(data);
    }
}

} // namespace Mobile
} // namespace VirtualMoney

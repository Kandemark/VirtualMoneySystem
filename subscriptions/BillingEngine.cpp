/**
 * @file BillingEngine.cpp
 * @brief Implementation of the BillingEngine class
 */

#include "BillingEngine.h"
#include <random>
#include <iostream>

bool BillingEngine::processBilling(const std::string& userId) {
    // Check if billing is due
    auto it = billingSchedule.find(userId);
    if (it == billingSchedule.end()) {
        std::cout << "[Billing] No billing schedule found for user: " << userId << std::endl;
        return false;
    }
    
    auto now = std::chrono::system_clock::now();
    if (now < it->second) {
        // Not yet due for billing
        return true;
    }
    
    // Process the billing
    std::cout << "[Billing] Processing billing for user: " << userId << std::endl;
    
    // Update next billing date (add 30 days)
    it->second = now + std::chrono::hours(24 * 30);
    
    return true;
}

std::string BillingEngine::generateInvoice(const std::string& userId, double amount) {
    // Generate unique invoice ID
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(100000, 999999);
    
    std::string invoiceId = "INV_" + std::to_string(dis(gen));
    
    std::cout << "[Billing] Generated invoice " << invoiceId 
              << " for $" << amount << std::endl;
    
    return invoiceId;
}

std::chrono::system_clock::time_point BillingEngine::getNextBillingDate(const std::string& userId) {
    auto it = billingSchedule.find(userId);
    if (it != billingSchedule.end()) {
        return it->second;
    }
    
    // Default to 30 days from now
    return std::chrono::system_clock::now() + std::chrono::hours(24 * 30);
}

bool BillingEngine::hasFailedPayments(const std::string& userId) {
    auto it = failedPayments.find(userId);
    return (it != failedPayments.end() && it->second > 0);
}

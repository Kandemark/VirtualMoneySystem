/**
 * @file SDKClient.cpp
 */

#include "SDKClient.h"
#include <iostream>
#include <sstream>

SDKClient::SDKClient(const std::string& apiKey, const std::string& environment)
    : apiKey(apiKey), environment(environment) {
    std::cout << "SDK initialized (" << environment << ")" << std::endl;
}

std::string SDKClient::createTransaction(const std::string& fromUserId, const std::string& toUserId, double amount) {
    std::stringstream ss;
    ss << "TX_" << (rand() % 1000000);
    
    std::cout << "Transaction created: " << fromUserId << " -> " << toUserId << " ($" << amount << ")" << std::endl;
    
    return ss.str();
}

double SDKClient::getBalance(const std::string& userId) {
    // In production, make API call
    return 1000.0;
}

bool SDKClient::verifyWebhook(const std::string& payload, const std::string& signature) {
    // In production, verify HMAC signature
    return !signature.empty();
}

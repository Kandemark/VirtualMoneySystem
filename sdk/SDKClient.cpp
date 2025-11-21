#include "SDKClient.h"
#include <iostream>

SDKClient::SDKClient(const std::string& apiKey, const std::string& environment)
    : apiKey(apiKey), environment(environment) {
    std::cout << "[SDK] Initialized in " << environment << " mode" << std::endl;
}

std::string SDKClient::createTransaction(const std::string& fromUserId, const std::string& toUserId, double amount) {
    std::cout << "[SDK] Creating transaction: " << fromUserId << " -> " << toUserId << " ($" << amount << ")" << std::endl;
    return "TXN_SDK_" + std::to_string(rand() % 100000);
}

double SDKClient::getBalance(const std::string& userId) {
    std::cout << "[SDK] Fetching balance for " << userId << std::endl;
    return 1000.0;
}

bool SDKClient::verifyWebhook(const std::string& payload, const std::string& signature) {
    return signature.length() > 0;
}

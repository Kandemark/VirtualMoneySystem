#include "GatewayAdapter.h"
#include <iostream>

void GatewayAdapter::registerGateway(const std::string& gatewayName, const std::string& apiKey) {
    gateways[gatewayName] = apiKey;
    std::cout << "[GatewayAdapter] Registered gateway: " << gatewayName << std::endl;
}

bool GatewayAdapter::sendToGateway(const std::string& gatewayName, const std::string& payload) {
    auto it = gateways.find(gatewayName);
    if (it != gateways.end()) {
        std::cout << "[GatewayAdapter] Sent to " << gatewayName << ": " << payload << std::endl;
        return true;
    }
    return false;
}

std::string GatewayAdapter::receiveFromGateway(const std::string& gatewayName, const std::string& transactionId) {
    return "{\"status\": \"success\", \"transactionId\": \"" + transactionId + "\"}";
}

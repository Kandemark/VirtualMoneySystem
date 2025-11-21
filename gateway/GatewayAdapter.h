#ifndef GATEWAY_ADAPTER_H
#define GATEWAY_ADAPTER_H
#include <string>
#include <map>

class GatewayAdapter {
public:
    void registerGateway(const std::string& gatewayName, const std::string& apiKey);
    bool sendToGateway(const std::string& gatewayName, const std::string& payload);
    std::string receiveFromGateway(const std::string& gatewayName, const std::string& transactionId);
private:
    std::map<std::string, std::string> gateways;
};

#endif

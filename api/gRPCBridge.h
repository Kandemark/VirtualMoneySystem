/**
 * @file gRPCBridge.h
 * @brief gRPC protocol bridge
 */

#ifndef GRPC_BRIDGE_H
#define GRPC_BRIDGE_H

#include <string>

class gRPCBridge {
public:
    void startServer(int port);
    void registerService(const std::string& serviceName);
    void handleRequest(const std::string& method, const std::string& request);
};

#endif

/**
 * @file gRPCBridge.cpp
 */

#include "gRPCBridge.h"
#include <iostream>

namespace VirtualMoney {

gRPCBridge::gRPCBridge() {}

void gRPCBridge::start(int port) {
    std::cout << "gRPC server started on port " << port << std::endl;
}

void gRPCBridge::stop() {
    std::cout << "gRPC server stopped" << std::endl;
}

std::string gRPCBridge::handleRequest(const std::string& method, const std::string& request) {
    std::cout << "gRPC request: " << method << std::endl;
    return "{\"status\": \"success\"}";
}

} // namespace VirtualMoney

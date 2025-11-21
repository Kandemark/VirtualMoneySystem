/**
 * @file RequestTracker.cpp
 */

#include "RequestTracker.h"
#include <iostream>
#include <random>
#include <sstream>
#include <iomanip>

namespace VirtualMoney {

RequestTracker::RequestTracker() {}

std::string RequestTracker::generateRequestId() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 15);
    
    std::stringstream ss;
    ss << "req_";
    
    const char* hex = "0123456789abcdef";
    for (int i = 0; i < 32; ++i) {
        ss << hex[dis(gen)];
    }
    
    return ss.str();
}

void RequestTracker::startRequest(const std::string& requestId, const std::string& path, const std::string& method) {
    RequestInfo info;
    info.requestId = requestId;
    info.path = path;
    info.method = method;
    info.startTime = std::chrono::system_clock::now();
    info.statusCode = 0;
    info.durationMs = 0;
    
    activeRequests[requestId] = info;
    
    std::cout << "Request started: " << requestId << " " << method << " " << path << std::endl;
}

void RequestTracker::endRequest(const std::string& requestId, int statusCode) {
    auto it = activeRequests.find(requestId);
    if (it != activeRequests.end()) {
        it->second.endTime = std::chrono::system_clock::now();
        it->second.statusCode = statusCode;
        
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
            it->second.endTime - it->second.startTime
        );
        it->second.durationMs = duration.count();
        
        std::cout << "Request completed: " << requestId 
                  << " [" << statusCode << "] " 
                  << it->second.durationMs << "ms" << std::endl;
        
        // Move to completed
        completedRequests[requestId] = it->second;
        activeRequests.erase(it);
    }
}

RequestInfo RequestTracker::getRequestInfo(const std::string& requestId) {
    auto it = activeRequests.find(requestId);
    if (it != activeRequests.end()) {
        return it->second;
    }
    
    auto it2 = completedRequests.find(requestId);
    if (it2 != completedRequests.end()) {
        return it2->second;
    }
    
    return RequestInfo();
}

std::vector<RequestInfo> RequestTracker::getActiveRequests() {
    std::vector<RequestInfo> requests;
    for (const auto& [id, info] : activeRequests) {
        requests.push_back(info);
    }
    return requests;
}

} // namespace VirtualMoney

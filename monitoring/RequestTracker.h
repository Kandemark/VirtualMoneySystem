/**
 * @file RequestTracker.h
 * @brief Request ID tracking across services
 */

#ifndef REQUEST_TRACKER_H
#define REQUEST_TRACKER_H

#include <string>
#include <map>
#include <chrono>

namespace VirtualMoney {

struct RequestInfo {
    std::string requestId;
    std::string path;
    std::string method;
    std::string userId;
    std::chrono::system_clock::time_point startTime;
    std::chrono::system_clock::time_point endTime;
    int statusCode;
    long long durationMs;
};

class RequestTracker {
public:
    RequestTracker();
    
    /**
     * @brief Generate unique request ID
     */
    std::string generateRequestId();
    
    /**
     * @brief Start tracking a request
     */
    void startRequest(const std::string& requestId, const std::string& path, const std::string& method);
    
    /**
     * @brief End tracking a request
     */
    void endRequest(const std::string& requestId, int statusCode);
    
    /**
     * @brief Get request info
     */
    RequestInfo getRequestInfo(const std::string& requestId);
    
    /**
     * @brief Get all active requests
     */
    std::vector<RequestInfo> getActiveRequests();
    
private:
    std::map<std::string, RequestInfo> activeRequests;
    std::map<std::string, RequestInfo> completedRequests;
};

} // namespace VirtualMoney

#endif

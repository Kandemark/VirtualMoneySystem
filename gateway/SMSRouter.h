/**
 * @file SMSRouter.h
 * @brief SMS command routing
 */

#ifndef SMS_ROUTER_H
#define SMS_ROUTER_H

#include <string>

class SMSRouter {
public:
    void routeCommand(const std::string& phoneNumber, const std::string& command);
    std::string processCommand(const std::string& command);
    void sendResponse(const std::string& phoneNumber, const std::string& response);
};

#endif

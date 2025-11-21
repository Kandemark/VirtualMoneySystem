/**
 * @file USSDHandler.h
 * @brief USSD protocol handler
 */

#ifndef USSD_HANDLER_H
#define USSD_HANDLER_H

#include <string>

class USSDHandler {
public:
    std::string handleUSSDRequest(const std::string& sessionId, const std::string& phoneNumber, const std::string& input);
    void registerMenu(const std::string& menuId, const std::string& menuStructure);
    std::string getMenuResponse(const std::string& menuId, const std::string& selection);
};

#endif

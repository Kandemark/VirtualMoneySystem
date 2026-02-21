#include "SMSRouter.h"

#include <iostream>

void SMSRouter::routeCommand(const std::string& phoneNumber, const std::string& command) { sendResponse(phoneNumber, processCommand(command)); }
std::string SMSRouter::processCommand(const std::string& command) { return "Processed:" + command; }
void SMSRouter::sendResponse(const std::string& phoneNumber, const std::string& response) { std::cout << "SMS->" << phoneNumber << ": " << response << std::endl; }

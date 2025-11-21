/**
 * @file ActionLogger.h
 * @brief Action logging system
 */

#ifndef ACTION_LOGGER_H
#define ACTION_LOGGER_H

#include <string>

class ActionLogger {
public:
    void logAction(const std::string& actor, const std::string& action, const std::string& target);
    void logAPICall(const std::string& endpoint, const std::string& method, const std::string& userId);
    std::string getActionLog(const std::string& actor);
};

#endif

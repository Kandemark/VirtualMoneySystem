/**
 * @file ActionLogger.h
 * @brief Action logging for logs directory
 */

#ifndef ACTION_LOGGER_LOGS_H
#define ACTION_LOGGER_LOGS_H

#include <string>

class ActionLoggerLogs {
public:
    void logAction(const std::string& action, const std::string& userId);
    void logToFile(const std::string& filename);
};

#endif

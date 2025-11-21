/**
 * @file EventLogger.h
 * @brief System event logging
 */

#ifndef EVENT_LOGGER_H
#define EVENT_LOGGER_H

#include <string>

class EventLogger {
public:
    void logEvent(const std::string& eventType, const std::string& eventData);
    void logError(const std::string& error, const std::string& context);
    void logWarning(const std::string& warning);
    std::string getEventLog(const std::string& eventType);
};

#endif

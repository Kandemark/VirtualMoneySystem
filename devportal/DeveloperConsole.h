/**
 * @file DeveloperConsole.h
 * @brief Developer portal console
 */

#ifndef DEVELOPER_CONSOLE_H
#define DEVELOPER_CONSOLE_H

#include <string>

class DeveloperConsole {
public:
    std::string createAPIKey(const std::string& developerId);
    void revokeAPIKey(const std::string& apiKey);
    std::string getAPIUsage(const std::string& apiKey);
    void setRateLimit(const std::string& apiKey, int limit);
};

#endif

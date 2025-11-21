/**
 * @file UserActionHistory.h
 * @brief User action history tracking
 */

#ifndef USER_ACTION_HISTORY_H
#define USER_ACTION_HISTORY_H

#include <string>
#include <vector>

class UserActionHistory {
public:
    void recordAction(const std::string& userId, const std::string& action, const std::string& details);
    std::vector<std::string> getActions(const std::string& userId, int limit = 100);
    void clearHistory(const std::string& userId);
};

#endif

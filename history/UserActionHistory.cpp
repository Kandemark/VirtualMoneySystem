#include "UserActionHistory.h"

#include <unordered_map>

namespace { std::unordered_map<std::string, std::vector<std::string>> g_actions; }

void UserActionHistory::recordAction(const std::string& userId, const std::string& action, const std::string& details) {
    g_actions[userId].push_back(action + ":" + details);
}

std::vector<std::string> UserActionHistory::getActions(const std::string& userId, int limit) {
    auto actions = g_actions[userId];
    if (limit > 0 && static_cast<int>(actions.size()) > limit) {
        actions.erase(actions.begin(), actions.end() - limit);
    }
    return actions;
}

void UserActionHistory::clearHistory(const std::string& userId) { g_actions.erase(userId); }

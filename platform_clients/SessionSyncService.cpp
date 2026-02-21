#include "SessionSyncService.h"

#include <unordered_map>

namespace {
std::unordered_map<std::string, std::string> g_userToSession;
std::unordered_map<std::string, std::string> g_sessionToUser;
}

void SessionSyncService::syncSession(const std::string& userId, const std::string& sessionData) {
    if (userId.empty() || sessionData.empty()) {
        return;
    }

    auto old = g_userToSession.find(userId);
    if (old != g_userToSession.end()) {
        g_sessionToUser.erase(old->second);
    }

    g_userToSession[userId] = sessionData;
    g_sessionToUser[sessionData] = userId;
}

std::string SessionSyncService::getSessionData(const std::string& userId) {
    auto it = g_userToSession.find(userId);
    return it == g_userToSession.end() ? "" : it->second;
}

void SessionSyncService::invalidateSession(const std::string& sessionId) {
    auto it = g_sessionToUser.find(sessionId);
    if (it == g_sessionToUser.end()) {
        return;
    }

    g_userToSession.erase(it->second);
    g_sessionToUser.erase(it);
}

bool SessionSyncService::isSessionValid(const std::string& sessionId) {
    return g_sessionToUser.find(sessionId) != g_sessionToUser.end();
}

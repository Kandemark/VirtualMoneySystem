#include "SessionSyncService.h"

#include <unordered_map>

namespace {
std::unordered_map<std::string, std::string> g_sessions;
}

void SessionSyncService::syncSession(const std::string& userId, const std::string& sessionData) {
    if (!userId.empty()) g_sessions[userId] = sessionData;
}

std::string SessionSyncService::getSessionData(const std::string& userId) {
    auto it = g_sessions.find(userId);
    return it == g_sessions.end() ? "" : it->second;
}

void SessionSyncService::invalidateSession(const std::string& sessionId) {
    g_sessions.erase(sessionId);
}

bool SessionSyncService::isSessionValid(const std::string& sessionId) {
    return g_sessions.find(sessionId) != g_sessions.end();
}

#include "SessionManager.h"
#include <iostream>

std::string SessionManager::createSession(const std::string& userId) {
    std::string sessionId = generateSessionId();
    SessionData data;
    data.userId = userId;
    data.createdAt = std::chrono::system_clock::now();
    data.lastActivity = data.createdAt;
    data.isActive = true;
    sessions[sessionId] = data;
    return sessionId;
}

bool SessionManager::validateSession(const std::string& sessionId) {
    auto it = sessions.find(sessionId);
    if (it == sessions.end()) return false;
    
    auto now = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::minutes>(now - it->second.lastActivity).count();
    
    if (elapsed > sessionTimeout) {
        sessions.erase(it);
        return false;
    }
    
    it->second.lastActivity = now;
    return it->second.isActive;
}

void SessionManager::terminateSession(const std::string& sessionId) {
    sessions.erase(sessionId);
}

SessionData SessionManager::getSessionData(const std::string& sessionId) const {
    return sessions.at(sessionId);
}

std::string SessionManager::generateSessionId() const {
    static const char hex[] = "0123456789abcdef";
    std::string id;
    for (int i = 0; i < 64; i++) id += hex[rand() % 16];
    return id;
}

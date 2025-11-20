#include "SessionValidator.h"
#include <random>
#include <sstream>
#include <iomanip>

SessionValidator::SessionValidator(int sessionTimeoutMinutes)
    : sessionTimeoutMinutes(sessionTimeoutMinutes) {}

std::string SessionValidator::createSession(const std::string& userId, const std::string& ipAddress, const std::string& userAgent) {
    std::string sessionId = generateSessionId();
    
    Session session;
    session.sessionId = sessionId;
    session.userId = userId;
    session.createdAt = std::chrono::system_clock::now();
    session.expiresAt = session.createdAt + std::chrono::minutes(sessionTimeoutMinutes);
    session.ipAddress = ipAddress;
    session.userAgent = userAgent;
    
    sessions[sessionId] = session;
    return sessionId;
}

bool SessionValidator::validateSession(const std::string& sessionId) const {
    auto it = sessions.find(sessionId);
    if (it == sessions.end()) {
        return false;
    }
    
    return std::chrono::system_clock::now() < it->second.expiresAt;
}

bool SessionValidator::invalidateSession(const std::string& sessionId) {
    return sessions.erase(sessionId) > 0;
}

void SessionValidator::invalidateAllUserSessions(const std::string& userId) {
    auto it = sessions.begin();
    while (it != sessions.end()) {
        if (it->second.userId == userId) {
            it = sessions.erase(it);
        } else {
            ++it;
        }
    }
}

Session SessionValidator::getSession(const std::string& sessionId) const {
    auto it = sessions.find(sessionId);
    if (it == sessions.end()) {
        throw std::runtime_error("Session not found");
    }
    return it->second;
}

std::string SessionValidator::generateSessionId() const {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 15);
    
    const char* hexChars = "0123456789abcdef";
    std::string sessionId;
    
    for (int i = 0; i < 64; i++) {
        sessionId += hexChars[dis(gen)];
    }
    
    return sessionId;
}

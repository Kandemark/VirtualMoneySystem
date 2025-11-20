#ifndef SESSION_VALIDATOR_H
#define SESSION_VALIDATOR_H

#include <string>
#include <map>
#include <chrono>

struct Session {
    std::string sessionId;
    std::string userId;
    std::chrono::system_clock::time_point createdAt;
    std::chrono::system_clock::time_point expiresAt;
    std::string ipAddress;
    std::string userAgent;
};

class SessionValidator {
public:
    SessionValidator(int sessionTimeoutMinutes = 30);

    std::string createSession(const std::string& userId, const std::string& ipAddress, const std::string& userAgent);
    bool validateSession(const std::string& sessionId) const;
    bool invalidateSession(const std::string& sessionId);
    void invalidateAllUserSessions(const std::string& userId);
    Session getSession(const std::string& sessionId) const;

private:
    std::map<std::string, Session> sessions;
    int sessionTimeoutMinutes;
    std::string generateSessionId() const;
};

#endif // SESSION_VALIDATOR_H

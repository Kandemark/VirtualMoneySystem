#ifndef SESSION_MANAGER_H
#define SESSION_MANAGER_H
#include <string>
#include <map>
#include <chrono>

struct SessionData {
    std::string userId;
    std::chrono::system_clock::time_point createdAt;
    std::chrono::system_clock::time_point lastActivity;
    bool isActive;
};

class SessionManager {
public:
    SessionManager(int sessionTimeout = 30) : sessionTimeout(sessionTimeout) {}
    std::string createSession(const std::string& userId);
    bool validateSession(const std::string& sessionId);
    void terminateSession(const std::string& sessionId);
    SessionData getSessionData(const std::string& sessionId) const;
private:
    std::map<std::string, SessionData> sessions;
    int sessionTimeout;
    std::string generateSessionId() const;
};

#endif

/**
 * @file SessionSyncService.h
 * @brief Cross-platform session synchronization
 */

#ifndef SESSION_SYNC_SERVICE_H
#define SESSION_SYNC_SERVICE_H

#include <string>

class SessionSyncService {
public:
    void syncSession(const std::string& userId, const std::string& sessionData);
    std::string getSessionData(const std::string& userId);
    void invalidateSession(const std::string& sessionId);
    bool isSessionValid(const std::string& sessionId);
};

#endif

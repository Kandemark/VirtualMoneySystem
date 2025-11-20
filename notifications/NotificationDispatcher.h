#ifndef NOTIFICATION_DISPATCHER_H
#define NOTIFICATION_DISPATCHER_H
#include <string>
#include <vector>

enum class NotificationType { EMAIL, SMS, PUSH, IN_APP };

class NotificationDispatcher {
public:
    bool sendNotification(const std::string& userId, const std::string& message, NotificationType type);
    bool sendBulkNotification(const std::vector<std::string>& userIds, const std::string& message, NotificationType type);
};

#endif

#include "NotificationDispatcher.h"
#include <iostream>

bool NotificationDispatcher::sendNotification(const std::string& userId, const std::string& message, NotificationType type) {
    std::cout << "[Notification] Sent to " << userId << ": " << message << std::endl;
    return true;
}

bool NotificationDispatcher::sendBulkNotification(const std::vector<std::string>& userIds, const std::string& message, NotificationType type) {
    for (const auto& userId : userIds) {
        sendNotification(userId, message, type);
    }
    return true;
}

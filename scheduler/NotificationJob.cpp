/**
 * @file NotificationJob.cpp
 */

#include "NotificationJob.h"
#include <iostream>

NotificationJob::NotificationJob() {}

void NotificationJob::scheduleNotification(const std::string& userId, const std::string& message, std::time_t sendAt) {
    Notification notif;
    notif.userId = userId;
    notif.message = message;
    notif.sendAt = sendAt;
    notif.sent = false;
    
    notifications.push_back(notif);
    std::cout << "Notification scheduled for " << userId << std::endl;
}

void NotificationJob::processPendingNotifications() {
    std::time_t now = std::time(nullptr);
    
    for (auto& notif : notifications) {
        if (!notif.sent && notif.sendAt <= now) {
            sendNotification(notif);
            notif.sent = true;
        }
    }
}

void NotificationJob::sendNotification(const Notification& notif) {
    std::cout << "Sending notification to " << notif.userId << ": " << notif.message << std::endl;
}

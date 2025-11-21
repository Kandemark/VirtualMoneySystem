/**
 * @file NotificationJob.h
 * @brief Scheduled notification jobs
 */

#ifndef NOTIFICATION_JOB_H
#define NOTIFICATION_JOB_H

#include <string>

class NotificationJob {
public:
    void scheduleNotification(const std::string& userId, const std::string& message, const std::string& time);
    void sendScheduledNotifications();
};

#endif

#ifndef IN_APP_NOTIFIER_H
#define IN_APP_NOTIFIER_H
#include <string>

class InAppNotifier {
public:
    bool sendInAppNotification(const std::string& userId, const std::string& title, const std::string& message);
    int getUnreadCount(const std::string& userId) const;
};

#endif

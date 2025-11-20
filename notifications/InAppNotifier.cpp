#include "InAppNotifier.h"
#include <iostream>

bool InAppNotifier::sendInAppNotification(const std::string& userId, const std::string& title, const std::string& message) {
    std::cout << "[InApp] User: " << userId << " Title: " << title << std::endl;
    return true;
}

int InAppNotifier::getUnreadCount(const std::string& userId) const {
    return 5;
}

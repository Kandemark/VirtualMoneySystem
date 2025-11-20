#include "UserInbox.h"

void UserInbox::addMessage(const std::string& userId, const InboxMessage& message) {
    inboxes[userId].push_back(message);
}

std::vector<InboxMessage> UserInbox::getMessages(const std::string& userId) const {
    auto it = inboxes.find(userId);
    return (it != inboxes.end()) ? it->second : std::vector<InboxMessage>{};
}

bool UserInbox::markAsRead(const std::string& userId, const std::string& messageId) {
    auto& messages = inboxes[userId];
    for (auto& msg : messages) {
        if (msg.messageId == messageId) {
            msg.isRead = true;
            return true;
        }
    }
    return false;
}

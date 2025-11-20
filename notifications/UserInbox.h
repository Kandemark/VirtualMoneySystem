#ifndef USER_INBOX_H
#define USER_INBOX_H
#include <string>
#include <vector>
#include <map>

struct InboxMessage {
    std::string messageId;
    std::string title;
    std::string content;
    bool isRead;
};

class UserInbox {
public:
    void addMessage(const std::string& userId, const InboxMessage& message);
    std::vector<InboxMessage> getMessages(const std::string& userId) const;
    bool markAsRead(const std::string& userId, const std::string& messageId);
private:
    std::map<std::string, std::vector<InboxMessage>> inboxes;
};

#endif

#ifndef EMAIL_NOTIFIER_H
#define EMAIL_NOTIFIER_H
#include <string>

class EmailNotifier {
public:
    bool sendEmail(const std::string& to, const std::string& subject, const std::string& body);
    bool sendTemplatedEmail(const std::string& to, const std::string& templateId, const std::string& data);
};

#endif

#include "EmailNotifier.h"
#include <iostream>

bool EmailNotifier::sendEmail(const std::string& to, const std::string& subject, const std::string& body) {
    std::cout << "[Email] To: " << to << " Subject: " << subject << std::endl;
    return true;
}

bool EmailNotifier::sendTemplatedEmail(const std::string& to, const std::string& templateId, const std::string& data) {
    return sendEmail(to, "Template: " + templateId, data);
}

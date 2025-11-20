#ifndef SMS_NOTIFIER_H
#define SMS_NOTIFIER_H
#include <string>

class SMSNotifier {
public:
    bool sendSMS(const std::string& phoneNumber, const std::string& message);
    bool sendOTP(const std::string& phoneNumber, const std::string& otp);
};

#endif

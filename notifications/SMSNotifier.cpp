#include "SMSNotifier.h"
#include <iostream>

bool SMSNotifier::sendSMS(const std::string& phoneNumber, const std::string& message) {
    std::cout << "[SMS] To: " << phoneNumber << " Message: " << message << std::endl;
    return true;
}

bool SMSNotifier::sendOTP(const std::string& phoneNumber, const std::string& otp) {
    return sendSMS(phoneNumber, "Your OTP is: " + otp);
}

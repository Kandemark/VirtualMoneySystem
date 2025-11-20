#include "MFAHandler.h"
#include <random>
#include <sstream>
#include <iomanip>

std::string MFAHandler::generateOTP(const std::string& userId) {
    std::string otp = generateRandomOTP();
    userOTPs[userId] = otp;
    return otp;
}

bool MFAHandler::verifyOTP(const std::string& userId, const std::string& otp) {
    auto it = userOTPs.find(userId);
    if (it != userOTPs.end() && it->second == otp) {
        userOTPs.erase(it);
        return true;
    }
    return false;
}

bool MFAHandler::enableMFA(const std::string& userId) {
    mfaStatus[userId] = true;
    return true;
}

bool MFAHandler::disableMFA(const std::string& userId) {
    mfaStatus[userId] = false;
    return true;
}

bool MFAHandler::isMFAEnabled(const std::string& userId) const {
    auto it = mfaStatus.find(userId);
    return (it != mfaStatus.end()) ? it->second : false;
}

std::string MFAHandler::generateRandomOTP() const {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(100000, 999999);
    std::ostringstream oss;
    oss << std::setw(6) << std::setfill('0') << dis(gen);
    return oss.str();
}

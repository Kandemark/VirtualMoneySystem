#ifndef MFA_HANDLER_H
#define MFA_HANDLER_H
#include <string>
#include <map>

class MFAHandler {
public:
    std::string generateOTP(const std::string& userId);
    bool verifyOTP(const std::string& userId, const std::string& otp);
    bool enableMFA(const std::string& userId);
    bool disableMFA(const std::string& userId);
    bool isMFAEnabled(const std::string& userId) const;
private:
    std::map<std::string, std::string> userOTPs;
    std::map<std::string, bool> mfaStatus;
    std::string generateRandomOTP() const;
};

#endif

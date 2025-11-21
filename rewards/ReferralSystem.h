#ifndef REFERRAL_SYSTEM_H
#define REFERRAL_SYSTEM_H
#include <string>
#include <map>
#include <vector>

class ReferralSystem {
public:
    std::string generateReferralCode(const std::string& userId);
    bool applyReferral(const std::string& newUserId, const std::string& referralCode);
    std::vector<std::string> getReferrals(const std::string& userId);
    double calculateReferralBonus(const std::string& userId);
private:
    std::map<std::string, std::string> referralCodes;
    std::map<std::string, std::vector<std::string>> referrals;
};

#endif

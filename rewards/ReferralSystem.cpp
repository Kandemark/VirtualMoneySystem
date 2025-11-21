#include "ReferralSystem.h"
#include <random>

std::string ReferralSystem::generateReferralCode(const std::string& userId) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 35);
    const char* chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::string code = "REF_";
    for (int i = 0; i < 8; i++) code += chars[dis(gen)];
    referralCodes[code] = userId;
    return code;
}

bool ReferralSystem::applyReferral(const std::string& newUserId, const std::string& referralCode) {
    auto it = referralCodes.find(referralCode);
    if (it != referralCodes.end()) {
        referrals[it->second].push_back(newUserId);
        return true;
    }
    return false;
}

std::vector<std::string> ReferralSystem::getReferrals(const std::string& userId) {
    auto it = referrals.find(userId);
    return (it != referrals.end()) ? it->second : std::vector<std::string>{};
}

double ReferralSystem::calculateReferralBonus(const std::string& userId) {
    return getReferrals(userId).size() * 10.0;
}

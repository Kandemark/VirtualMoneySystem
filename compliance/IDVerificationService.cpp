#include "IDVerificationService.h"

#include <unordered_map>

namespace { std::unordered_map<std::string, std::string> g_verification; }

bool IDVerificationService::verifyID(const std::string& userId, const std::string& idNumber, const std::string&) {
    const bool ok = !userId.empty() && idNumber.size() >= 6;
    g_verification[userId] = ok ? "VERIFIED" : "REJECTED";
    return ok;
}

std::string IDVerificationService::getVerificationStatus(const std::string& userId) { return g_verification[userId].empty()?"PENDING":g_verification[userId]; }
void IDVerificationService::requestManualReview(const std::string& userId) { g_verification[userId] = "MANUAL_REVIEW"; }

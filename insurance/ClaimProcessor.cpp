#include "ClaimProcessor.h"
#include <iostream>

bool ClaimProcessor::processClaim(const std::string& claimId) {
    std::cout << "[Claims] Processing claim " << claimId << std::endl;
    return true;
}

void ClaimProcessor::approveClaim(const std::string& claimId, double approvedAmount) {
    auto it = claims.find(claimId);
    if (it != claims.end()) {
        it->second.status = ClaimStatus::APPROVED;
        it->second.amount = approvedAmount;
    }
}

void ClaimProcessor::rejectClaim(const std::string& claimId, const std::string& reason) {
    auto it = claims.find(claimId);
    if (it != claims.end()) {
        it->second.status = ClaimStatus::REJECTED;
        it->second.reason = reason;
    }
}

ClaimStatus ClaimProcessor::getClaimStatus(const std::string& claimId) {
    auto it = claims.find(claimId);
    return (it != claims.end()) ? it->second.status : ClaimStatus::PENDING;
}

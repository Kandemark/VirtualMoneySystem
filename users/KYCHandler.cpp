#include "KYCHandler.h"
#include <stdexcept>

KYCHandler::KYCHandler() {}

bool KYCHandler::submitKYC(const std::string& userId, const std::string& documentType, const std::string& documentNumber, const std::string& issuingCountry) {
    KYCData data;
    data.userId = userId;
    data.documentType = documentType;
    data.documentNumber = documentNumber;
    data.issuingCountry = issuingCountry;
    data.submittedAt = std::chrono::system_clock::now();
    data.status = KYCStatus::PENDING;
    
    kycRecords[userId] = data;
    return true;
}

KYCStatus KYCHandler::getKYCStatus(const std::string& userId) const {
    auto it = kycRecords.find(userId);
    if (it == kycRecords.end()) {
        return KYCStatus::NOT_STARTED;
    }
    return it->second.status;
}

bool KYCHandler::approveKYC(const std::string& userId, const std::string& reviewNotes) {
    auto it = kycRecords.find(userId);
    if (it == kycRecords.end()) {
        return false;
    }
    
    it->second.status = KYCStatus::APPROVED;
    it->second.reviewNotes = reviewNotes;
    return true;
}

bool KYCHandler::rejectKYC(const std::string& userId, const std::string& reviewNotes) {
    auto it = kycRecords.find(userId);
    if (it == kycRecords.end()) {
        return false;
    }
    
    it->second.status = KYCStatus::REJECTED;
    it->second.reviewNotes = reviewNotes;
    return true;
}

KYCData KYCHandler::getKYCData(const std::string& userId) const {
    auto it = kycRecords.find(userId);
    if (it == kycRecords.end()) {
        throw std::runtime_error("KYC data not found for user: " + userId);
    }
    return it->second;
}

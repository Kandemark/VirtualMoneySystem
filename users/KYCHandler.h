#ifndef KYC_HANDLER_H
#define KYC_HANDLER_H

#include <string>
#include <map>
#include <chrono>

enum class KYCStatus {
    NOT_STARTED,
    PENDING,
    APPROVED,
    REJECTED,
    REQUIRES_REVIEW
};

struct KYCData {
    std::string userId;
    std::string documentType;
    std::string documentNumber;
    std::string issuingCountry;
    std::chrono::system_clock::time_point submittedAt;
    KYCStatus status;
    std::string reviewNotes;
};

class KYCHandler {
public:
    KYCHandler();

    bool submitKYC(const std::string& userId, const std::string& documentType, const std::string& documentNumber, const std::string& issuingCountry);
    KYCStatus getKYCStatus(const std::string& userId) const;
    bool approveKYC(const std::string& userId, const std::string& reviewNotes = "");
    bool rejectKYC(const std::string& userId, const std::string& reviewNotes);
    KYCData getKYCData(const std::string& userId) const;

private:
    std::map<std::string, KYCData> kycRecords;
};

#endif // KYC_HANDLER_H

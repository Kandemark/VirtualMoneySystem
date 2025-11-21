/**
 * @file IDVerificationService.h
 * @brief ID verification service
 */

#ifndef ID_VERIFICATION_SERVICE_H
#define ID_VERIFICATION_SERVICE_H

#include <string>

class IDVerificationService {
public:
    bool verifyID(const std::string& userId, const std::string& idNumber, const std::string& idType);
    std::string getVerificationStatus(const std::string& userId);
    void requestManualReview(const std::string& userId);
};

#endif

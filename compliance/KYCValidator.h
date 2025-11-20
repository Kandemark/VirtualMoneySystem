#ifndef KYC_VALIDATOR_H
#define KYC_VALIDATOR_H

#include <string>

class KYCValidator {
public:
    // Validates if a user ID meets the required format/criteria
    bool validateUserId(const std::string& userId);
};

#endif // KYC_VALIDATOR_H

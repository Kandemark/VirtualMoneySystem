#include "KYCValidator.h"
#include <regex>

bool KYCValidator::validateUserId(const std::string& userId) {
    // Basic validation: User ID must be alphanumeric and at least 3 characters long
    if (userId.length() < 3) return false;
    
    static const std::regex pattern("^[a-zA-Z0-9_]+$");
    return std::regex_match(userId, pattern);
}

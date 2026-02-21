#include "InputValidator.h"
#include <algorithm>
#include <cctype>

// Regex patterns
const std::regex InputValidator::USERNAME_REGEX(R"(^[a-zA-Z0-9_]{3,20}$)");
const std::regex InputValidator::EMAIL_REGEX(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
const std::regex InputValidator::PASSWORD_REGEX(R"(^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[@$!%*?&])[A-Za-z\d@$!%*?&]{8,}$)");
const std::regex InputValidator::WALLET_ID_REGEX(R"(^wallet_\d+_\d+$)");
const std::regex InputValidator::AMOUNT_REGEX(R"(^\d+(\.\d{1,8})?$)");
const std::regex InputValidator::TRANSACTION_ID_REGEX(R"(^tx_\d+_\d+$)");
const std::regex InputValidator::JWT_REGEX(R"(^[A-Za-z0-9_-]+\.[A-Za-z0-9_-]+\.[A-Za-z0-9_-]+$)");
const std::regex InputValidator::SQL_INJECTION_REGEX(R"((union|select|insert|update|delete|drop|create|alter|exec|script|javascript|vbscript))", std::regex_constants::icase);
const std::regex InputValidator::XSS_REGEX(R"((<script|</script|javascript:|vbscript:|onload=|onerror=|onclick=))", std::regex_constants::icase);

bool InputValidator::isValidUsername(const std::string& username) {
    if (username.empty() || username.length() > 20) return false;
    return std::regex_match(username, USERNAME_REGEX);
}

bool InputValidator::isValidEmail(const std::string& email) {
    if (email.empty() || email.length() > 254) return false;
    return std::regex_match(email, EMAIL_REGEX);
}

bool InputValidator::isValidPassword(const std::string& password) {
    if (password.empty() || password.length() > 128) return false;
    return std::regex_match(password, PASSWORD_REGEX);
}

bool InputValidator::isValidWalletId(const std::string& walletId) {
    if (walletId.empty() || walletId.length() > 50) return false;
    return std::regex_match(walletId, WALLET_ID_REGEX);
}

bool InputValidator::isValidAmount(const std::string& amount) {
    if (amount.empty() || amount.length() > 20) return false;
    
    if (!std::regex_match(amount, AMOUNT_REGEX)) return false;
    
    try {
        double value = std::stod(amount);
        return value > 0 && value <= 1000000000; // Max 1 billion
    } catch (...) {
        return false;
    }
}

bool InputValidator::isValidCurrency(const std::string& currency) {
    if (currency.empty() || currency.length() != 3) return false;
    
    std::string upperCurrency = currency;
    std::transform(upperCurrency.begin(), upperCurrency.end(), upperCurrency.begin(), ::toupper);
    
    return upperCurrency == "USD" || upperCurrency == "EUR" || 
           upperCurrency == "KES" || upperCurrency == "BTC";
}

bool InputValidator::isValidTransactionId(const std::string& txId) {
    if (txId.empty() || txId.length() > 50) return false;
    return std::regex_match(txId, TRANSACTION_ID_REGEX);
}

bool InputValidator::isValidJWT(const std::string& token) {
    if (token.empty() || token.length() > 1024) return false;
    return std::regex_match(token, JWT_REGEX);
}

std::string InputValidator::sanitizeString(const std::string& input) {
    std::string sanitized = input;
    
    // Remove potentially dangerous characters
    sanitized.erase(std::remove(sanitized.begin(), sanitized.end(), '\0'), sanitized.end());
    sanitized.erase(std::remove(sanitized.begin(), sanitized.end(), '\r'), sanitized.end());
    sanitized.erase(std::remove(sanitized.begin(), sanitized.end(), '\n'), sanitized.end());
    
    // Trim whitespace
    sanitized.erase(0, sanitized.find_first_not_of(" \t\n\r\f\v"));
    sanitized.erase(sanitized.find_last_not_of(" \t\n\r\f\v") + 1);
    
    return sanitized;
}

bool InputValidator::containsSQLInjection(const std::string& input) {
    return std::regex_search(input, SQL_INJECTION_REGEX);
}

bool InputValidator::containsXSS(const std::string& input) {
    return std::regex_search(input, XSS_REGEX);
}

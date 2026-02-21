#ifndef INPUT_VALIDATOR_H
#define INPUT_VALIDATOR_H

#include <string>
#include <regex>

class InputValidator {
public:
    // Username validation: 3-20 chars, alphanumeric + underscore
    static bool isValidUsername(const std::string& username);
    
    // Email validation: basic email format
    static bool isValidEmail(const std::string& email);
    
    // Password validation: 8+ chars, at least one uppercase, lowercase, digit, special char
    static bool isValidPassword(const std::string& password);
    
    // Wallet ID validation: wallet_ followed by timestamp and random number
    static bool isValidWalletId(const std::string& walletId);
    
    // Amount validation: positive number with up to 8 decimal places
    static bool isValidAmount(const std::string& amount);
    
    // Currency validation: USD, EUR, KES, BTC
    static bool isValidCurrency(const std::string& currency);
    
    // Transaction ID validation: tx_ followed by timestamp and random number
    static bool isValidTransactionId(const std::string& txId);
    
    // JWT token validation: basic format check
    static bool isValidJWT(const std::string& token);
    
    // Generic string sanitization
    static std::string sanitizeString(const std::string& input);
    
    // Check for SQL injection patterns
    static bool containsSQLInjection(const std::string& input);
    
    // Check for XSS patterns
    static bool containsXSS(const std::string& input);

private:
    static const std::regex USERNAME_REGEX;
    static const std::regex EMAIL_REGEX;
    static const std::regex PASSWORD_REGEX;
    static const std::regex WALLET_ID_REGEX;
    static const std::regex AMOUNT_REGEX;
    static const std::regex TRANSACTION_ID_REGEX;
    static const std::regex JWT_REGEX;
    static const std::regex SQL_INJECTION_REGEX;
    static const std::regex XSS_REGEX;
};

#endif // INPUT_VALIDATOR_H

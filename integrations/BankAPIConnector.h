/**
 * @file BankAPIConnector.h
 * @brief Connect to bank APIs
 */

#ifndef BANK_API_CONNECTOR_H
#define BANK_API_CONNECTOR_H

#include <string>

class BankAPIConnector {
public:
    bool connect(const std::string& bankId, const std::string& apiKey);
    std::string getAccountBalance(const std::string& accountNumber);
    bool initiateTransfer(const std::string& fromAccount, const std::string& toAccount, double amount);
    std::string getTransactionStatus(const std::string& transactionId);
};

#endif

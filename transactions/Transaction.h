#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <chrono>

class Transaction {
public:
    Transaction(std::string senderId, std::string receiverId, double amount, std::string currency);

    std::string getSenderId() const;
    std::string getReceiverId() const;
    double getAmount() const;
    std::string getCurrency() const;
    std::chrono::system_clock::time_point getTimestamp() const;

private:
    std::string senderId;
    std::string receiverId;
    double amount;
    std::string currency;
    std::chrono::system_clock::time_point timestamp;
};

#endif // TRANSACTION_H

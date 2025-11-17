#include "Transaction.h"

Transaction::Transaction(std::string senderId, std::string receiverId, double amount, std::string currency)
    : senderId(senderId),
      receiverId(receiverId),
      amount(amount),
      currency(currency),
      timestamp(std::chrono::system_clock::now()) {}

std::string Transaction::getSenderId() const {
    return senderId;
}

std::string Transaction::getReceiverId() const {
    return receiverId;
}

double Transaction::getAmount() const {
    return amount;
}

std::string Transaction::getCurrency() const {
    return currency;
}

std::chrono::system_clock::time_point Transaction::getTimestamp() const {
    return timestamp;
}

/**
 * @file PaymentTracker.h
 * @brief Track invoice payments and reminders
 */

#ifndef PAYMENT_TRACKER_H
#define PAYMENT_TRACKER_H

#include <string>
#include <map>

class PaymentTracker {
public:
    void recordPayment(const std::string& invoiceId, double amount);
    double getAmountPaid(const std::string& invoiceId);
    double getAmountDue(const std::string& invoiceId, double totalAmount);
    bool isFullyPaid(const std::string& invoiceId, double totalAmount);
private:
    std::map<std::string, double> payments;
};

#endif

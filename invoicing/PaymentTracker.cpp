#include "PaymentTracker.h"

void PaymentTracker::recordPayment(const std::string& invoiceId, double amount) {
    payments[invoiceId] += amount;
}

double PaymentTracker::getAmountPaid(const std::string& invoiceId) {
    auto it = payments.find(invoiceId);
    return (it != payments.end()) ? it->second : 0.0;
}

double PaymentTracker::getAmountDue(const std::string& invoiceId, double totalAmount) {
    return totalAmount - getAmountPaid(invoiceId);
}

bool PaymentTracker::isFullyPaid(const std::string& invoiceId, double totalAmount) {
    return getAmountPaid(invoiceId) >= totalAmount;
}

/**
 * @file PaymentScheduler.cpp
 */

#include "PaymentScheduler.h"
#include <iostream>

PaymentScheduler::PaymentScheduler() {}

void PaymentScheduler::schedulePayment(const std::string& from, const std::string& to, double amount, std::time_t executeAt) {
    ScheduledPayment payment;
    payment.from = from;
    payment.to = to;
    payment.amount = amount;
    payment.executeAt = executeAt;
    payment.executed = false;
    
    scheduledPayments.push_back(payment);
    std::cout << "Payment scheduled: $" << amount << " from " << from << " to " << to << std::endl;
}

void PaymentScheduler::processPendingPayments() {
    std::time_t now = std::time(nullptr);
    
    for (auto& payment : scheduledPayments) {
        if (!payment.executed && payment.executeAt <= now) {
            executePayment(payment);
            payment.executed = true;
        }
    }
}

void PaymentScheduler::executePayment(const ScheduledPayment& payment) {
    std::cout << "Executing scheduled payment: $" << payment.amount 
              << " from " << payment.from << " to " << payment.to << std::endl;
}

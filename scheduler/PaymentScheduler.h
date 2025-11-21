/**
 * @file PaymentScheduler.h
 * @brief Payment scheduling system
 */

#ifndef PAYMENT_SCHEDULER_H
#define PAYMENT_SCHEDULER_H

#include <string>

class PaymentScheduler {
public:
    void schedulePayment(const std::string& userId, double amount, const std::string& schedule);
    void processScheduledPayments();
};

#endif

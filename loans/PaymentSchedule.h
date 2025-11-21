/**
 * @file PaymentSchedule.h
 * @brief Loan payment schedule management
 */

#ifndef PAYMENT_SCHEDULE_H
#define PAYMENT_SCHEDULE_H

#include <string>
#include <vector>
#include <chrono>

struct ScheduledPayment {
    int paymentNumber;
    std::chrono::system_clock::time_point dueDate;
    double amount;
    double principal;
    double interest;
    bool isPaid;
};

class PaymentSchedule {
public:
    std::vector<ScheduledPayment> generateSchedule(const std::string& loanId, double monthlyPayment, int termMonths);
    void markPaymentPaid(const std::string& loanId, int paymentNumber);
    std::vector<ScheduledPayment> getUpcomingPayments(const std::string& loanId);
private:
    std::map<std::string, std::vector<ScheduledPayment>> schedules;
};

#endif

#include "PaymentSchedule.h"

std::vector<ScheduledPayment> PaymentSchedule::generateSchedule(const std::string& loanId, double monthlyPayment, int termMonths) {
    std::vector<ScheduledPayment> schedule;
    auto startDate = std::chrono::system_clock::now();
    
    for (int i = 0; i < termMonths; i++) {
        ScheduledPayment payment;
        payment.paymentNumber = i + 1;
        payment.dueDate = startDate + std::chrono::hours(24 * 30 * (i + 1));
        payment.amount = monthlyPayment;
        payment.principal = monthlyPayment * 0.7;
        payment.interest = monthlyPayment * 0.3;
        payment.isPaid = false;
        schedule.push_back(payment);
    }
    
    schedules[loanId] = schedule;
    return schedule;
}

void PaymentSchedule::markPaymentPaid(const std::string& loanId, int paymentNumber) {
    auto& schedule = schedules[loanId];
    if (paymentNumber > 0 && paymentNumber <= static_cast<int>(schedule.size())) {
        schedule[paymentNumber - 1].isPaid = true;
    }
}

std::vector<ScheduledPayment> PaymentSchedule::getUpcomingPayments(const std::string& loanId) {
    std::vector<ScheduledPayment> upcoming;
    auto& schedule = schedules[loanId];
    for (const auto& payment : schedule) {
        if (!payment.isPaid) {
            upcoming.push_back(payment);
        }
    }
    return upcoming;
}

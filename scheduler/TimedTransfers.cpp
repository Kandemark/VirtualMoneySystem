/**
 * @file TimedTransfers.cpp
 */

#include "TimedTransfers.h"
#include <iostream>

TimedTransfers::TimedTransfers() {}

void TimedTransfers::scheduleRecurringTransfer(const std::string& from, const std::string& to, 
                                               double amount, int intervalDays) {
    RecurringTransfer transfer;
    transfer.from = from;
    transfer.to = to;
    transfer.amount = amount;
    transfer.intervalDays = intervalDays;
    transfer.nextExecution = std::time(nullptr) + (intervalDays * 86400);
    transfer.active = true;
    
    recurringTransfers.push_back(transfer);
    std::cout << "Recurring transfer scheduled: $" << amount << " every " << intervalDays << " days" << std::endl;
}

void PaymentScheduler::processRecurringTransfers() {
    std::time_t now = std::time(nullptr);
    
    for (auto& transfer : recurringTransfers) {
        if (transfer.active && transfer.nextExecution <= now) {
            executeTransfer(transfer);
            transfer.nextExecution = now + (transfer.intervalDays * 86400);
        }
    }
}

void TimedTransfers::executeTransfer(const RecurringTransfer& transfer) {
    std::cout << "Executing recurring transfer: $" << transfer.amount 
              << " from " << transfer.from << " to " << transfer.to << std::endl;
}

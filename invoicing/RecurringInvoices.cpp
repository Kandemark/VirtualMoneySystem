#include "RecurringInvoices.h"
#include <iostream>

void RecurringInvoices::setupRecurring(const std::string& customerId, const std::string& frequency, double amount) {
    recurringSetup[customerId] = {frequency, amount};
}

void RecurringInvoices::processRecurring() {
    for (const auto& [customerId, setup] : recurringSetup) {
        std::cout << "[Recurring] Generating invoice for " << customerId << " - $" << setup.second << std::endl;
    }
}

void RecurringInvoices::cancelRecurring(const std::string& customerId) {
    recurringSetup.erase(customerId);
}

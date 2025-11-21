/**
 * @file RecurringInvoices.h
 * @brief Automated recurring invoice generation
 */

#ifndef RECURRING_INVOICES_H
#define RECURRING_INVOICES_H

#include <string>
#include <map>

class RecurringInvoices {
public:
    void setupRecurring(const std::string& customerId, const std::string& frequency, double amount);
    void processRecurring();
    void cancelRecurring(const std::string& customerId);
private:
    std::map<std::string, std::pair<std::string, double>> recurringSetup;
};

#endif

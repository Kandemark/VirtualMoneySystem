/**
 * @file InvoiceGenerator.h
 * @brief Invoice creation and management
 */

#ifndef INVOICE_GENERATOR_H
#define INVOICE_GENERATOR_H

#include <string>
#include <vector>
#include <map>

struct InvoiceItem {
    std::string description;
    int quantity;
    double unitPrice;
    double total;
};

struct Invoice {
    std::string invoiceId;
    std::string customerId;
    std::vector<InvoiceItem> items;
    double subtotal;
    double tax;
    double total;
    std::string dueDate;
    std::string status;
};

class InvoiceGenerator {
public:
    std::string createInvoice(const std::string& customerId);
    void addItem(const std::string& invoiceId, const std::string& description, int quantity, double unitPrice);
    Invoice getInvoice(const std::string& invoiceId);
    void finalizeInvoice(const std::string& invoiceId);
private:
    std::map<std::string, Invoice> invoices;
};

#endif

#include "InvoiceGenerator.h"

std::string InvoiceGenerator::createInvoice(const std::string& customerId) {
    Invoice invoice;
    invoice.invoiceId = "INV_" + std::to_string(invoices.size() + 1);
    invoice.customerId = customerId;
    invoice.subtotal = 0.0;
    invoice.tax = 0.0;
    invoice.total = 0.0;
    invoice.dueDate = "2024-02-01";
    invoice.status = "draft";
    
    invoices[invoice.invoiceId] = invoice;
    return invoice.invoiceId;
}

void InvoiceGenerator::addItem(const std::string& invoiceId, const std::string& description, int quantity, double unitPrice) {
    auto& invoice = invoices[invoiceId];
    
    InvoiceItem item;
    item.description = description;
    item.quantity = quantity;
    item.unitPrice = unitPrice;
    item.total = quantity * unitPrice;
    
    invoice.items.push_back(item);
    invoice.subtotal += item.total;
}

Invoice InvoiceGenerator::getInvoice(const std::string& invoiceId) {
    return invoices.at(invoiceId);
}

void InvoiceGenerator::finalizeInvoice(const std::string& invoiceId) {
    auto& invoice = invoices[invoiceId];
    invoice.tax = invoice.subtotal * 0.1;
    invoice.total = invoice.subtotal + invoice.tax;
    invoice.status = "sent";
}

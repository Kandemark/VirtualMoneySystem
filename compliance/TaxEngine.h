/**
 * @file TaxEngine.h
 * @brief Tax calculation and compliance engine
 */

#ifndef TAX_ENGINE_H
#define TAX_ENGINE_H

#include <string>

class TaxEngine {
public:
    double calculateTax(double amount, const std::string& taxType, const std::string& region);
    void setTaxRate(const std::string& taxType, const std::string& region, double rate);
    std::string generateTaxReport(const std::string& userId, const std::string& period);
};

#endif

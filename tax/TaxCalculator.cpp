#include "TaxCalculator.h"

double TaxCalculator::calculateSalesTax(double amount, const std::string& region) {
    double rate = getTaxRate(region);
    return amount * (rate / 100.0);
}

double TaxCalculator::calculateIncomeTax(double income, const std::string& filingStatus) {
    if (income < 10000) return 0.0;
    if (income < 50000) return income * 0.10;
    if (income < 100000) return income * 0.20;
    return income * 0.30;
}

double TaxCalculator::getTaxRate(const std::string& region) {
    if (region == "US") return 7.5;
    if (region == "EU") return 20.0;
    if (region == "UK") return 20.0;
    return 0.0;
}

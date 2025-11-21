#include "TaxCompliance.h"

bool TaxCompliance::isCompliant(const std::string& userId) {
    return true; // Simplified check
}

std::string TaxCompliance::fileTaxReturn(const std::string& userId, int year) {
    return "FILING_" + std::to_string(year) + "_" + userId;
}

std::string TaxCompliance::getFilingDeadline(const std::string& region) {
    if (region == "US") return "April 15";
    if (region == "UK") return "January 31";
    return "December 31";
}

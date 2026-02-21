#include "TaxEngine.h"

#include <unordered_map>

namespace { std::unordered_map<std::string, double> g_rates; }

double TaxEngine::calculateTax(double amount, const std::string& taxType, const std::string& region) {
    if (amount <= 0.0) return 0.0;
    const std::string key = taxType + ":" + region;
    const double rate = g_rates.count(key) ? g_rates[key] : 0.0;
    return amount * rate;
}
void TaxEngine::setTaxRate(const std::string& taxType, const std::string& region, double rate) { g_rates[taxType + ":" + region] = rate; }
std::string TaxEngine::generateTaxReport(const std::string& userId, const std::string& period) { return "tax-report:" + userId + ":" + period; }

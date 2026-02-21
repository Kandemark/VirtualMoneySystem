#include "SmartFXRules.h"

#include <algorithm>

namespace {
double g_threshold = 1000.0;
}

double SmartFXRules::applyRules(const std::string& fromCurrency, const std::string& toCurrency, double amount) {
    if (amount <= 0.0 || fromCurrency.empty() || toCurrency.empty()) return 0.0;
    if (fromCurrency == toCurrency) return amount;
    if (amount >= g_threshold) {
        return amount * 0.998; // large-amount routing discount
    }
    return amount * 0.9995;
}

std::string SmartFXRules::getBestConversionTime(const std::string& currencyPair) {
    if (currencyPair.find("BTC") != std::string::npos) return "00:00-06:00 UTC";
    return "09:00-16:00 UTC";
}

void SmartFXRules::setThreshold(double threshold) {
    g_threshold = std::max(0.0, threshold);
}

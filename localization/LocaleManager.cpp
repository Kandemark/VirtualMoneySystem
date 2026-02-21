#include "LocaleManager.h"

#include <iomanip>
#include <sstream>

void LocaleManager::setLocale(const std::string& locale) { currentLocale = locale; }
std::string LocaleManager::getLocale() { return currentLocale; }

std::string LocaleManager::formatCurrency(double amount, const std::string& currencyCode) {
    std::ostringstream oss; oss << currencyCode << ' ' << std::fixed << std::setprecision(2) << amount; return oss.str();
}

std::string LocaleManager::formatDate(const std::string& date, const std::string& format) { return format + ":" + date; }

std::string LocaleManager::formatNumber(double number) { std::ostringstream oss; oss << number; return oss.str(); }

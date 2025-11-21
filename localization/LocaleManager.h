/**
 * @file LocaleManager.h
 * @brief Locale and regional settings
 */

#ifndef LOCALE_MANAGER_H
#define LOCALE_MANAGER_H

#include <string>

class LocaleManager {
public:
    void setLocale(const std::string& locale);
    std::string getLocale();
    std::string formatCurrency(double amount, const std::string& currencyCode);
    std::string formatDate(const std::string& date, const std::string& format);
    std::string formatNumber(double number);

private:
    std::string currentLocale = "en_US";
};

#endif

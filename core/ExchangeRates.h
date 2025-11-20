#ifndef EXCHANGE_RATES_H
#define EXCHANGE_RATES_H

#include <string>
#include <map>
#include <chrono>

struct ExchangeRate {
    std::string fromCurrency;
    std::string toCurrency;
    double rate;
    std::chrono::system_clock::time_point lastUpdated;
};

class ExchangeRates {
public:
    ExchangeRates();

    void setRate(const std::string& from, const std::string& to, double rate);
    double getRate(const std::string& from, const std::string& to) const;
    double convert(double amount, const std::string& from, const std::string& to) const;
    bool hasRate(const std::string& from, const std::string& to) const;

private:
    std::map<std::pair<std::string, std::string>, ExchangeRate> rates;
    std::string getRateKey(const std::string& from, const std::string& to) const;
    void initializeDefaultRates();
};

#endif // EXCHANGE_RATES_H

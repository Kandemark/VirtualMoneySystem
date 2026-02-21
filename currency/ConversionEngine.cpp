
#include "ConversionEngine.h"

#include "ExchangeRates.h"

#include <cstdlib>

namespace {
int getSpreadBps() {
  int spreadBps = 20;
  const char *env = std::getenv("VMS_FX_SPREAD_BPS");
  if (env && *env) {
    try {
      spreadBps = std::stoi(std::string(env));
    } catch (...) {
      spreadBps = 20;
    }
  }
  if (spreadBps < 0) spreadBps = 0;
  if (spreadBps > 500) spreadBps = 500;
  return spreadBps;
}
} // namespace

double ConversionEngine::getRate(const std::string &fromCurrency,
                                 const std::string &toCurrency) {
  ExchangeRates rates;
  const double midRate = rates.getRate(fromCurrency, toCurrency);
  if (midRate <= 0.0) {
    return 0.0;
  }

  const int spreadBps = getSpreadBps();
  const double spreadMultiplier = 1.0 - (static_cast<double>(spreadBps) / 10000.0);
  return midRate * spreadMultiplier;
}

double ConversionEngine::convert(double amount, const std::string &fromCurrency,
                                 const std::string &toCurrency) {
  if (amount <= 0.0) {
    return 0.0;
  }
  const double rate = getRate(fromCurrency, toCurrency);
  if (rate <= 0.0) {
    return 0.0;
  }
  return amount * rate;
}

void ConversionEngine::updateRates() {
  ExchangeRates rates;
  rates.fetchLatestRates();
}

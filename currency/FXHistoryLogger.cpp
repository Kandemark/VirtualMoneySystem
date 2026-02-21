
#include "FXHistoryLogger.h"

#include <algorithm>
#include <ctime>
#include <mutex>
#include <numeric>
#include <sstream>

namespace {
std::mutex g_histMutex;

std::string nowTimestampUtc() {
  std::time_t t = std::time(nullptr);
  std::tm tm{};
  gmtime_s(&tm, &t);
  char buf[32];
  std::strftime(buf, sizeof(buf), "%Y-%m-%dT%H:%M:%SZ", &tm);
  return std::string(buf);
}
} // namespace

void FXHistoryLogger::logRate(const std::string &currencyPair, double rate) {
  if (currencyPair.empty() || rate <= 0.0) {
    return;
  }
  std::lock_guard<std::mutex> lock(g_histMutex);
  FXHistoryEntry entry;
  entry.currencyPair = currencyPair;
  entry.rate = rate;
  entry.timestamp = nowTimestampUtc();
  history.push_back(entry);

  // Keep memory bounded
  if (history.size() > 5000) {
    history.erase(history.begin(), history.begin() + 1000);
  }
}

std::vector<FXHistoryEntry> FXHistoryLogger::getHistory(const std::string &currencyPair,
                                                       int days) {
  std::lock_guard<std::mutex> lock(g_histMutex);
  if (days <= 0) {
    days = 30;
  }

  std::vector<FXHistoryEntry> out;
  for (const auto &e : history) {
    if (e.currencyPair == currencyPair) {
      out.push_back(e);
    }
  }
  return out;
}

double FXHistoryLogger::getAverageRate(const std::string &currencyPair, int days) {
  const auto entries = getHistory(currencyPair, days);
  if (entries.empty()) {
    return 0.0;
  }
  double sum = 0.0;
  for (const auto &e : entries) {
    sum += e.rate;
  }
  return sum / static_cast<double>(entries.size());
}


#include "FeeSummaryGenerator.h"

#include <mutex>
#include <sstream>
#include <unordered_map>

namespace {
std::mutex g_feeSumMutex;
// Key: userId|period
std::unordered_map<std::string, double> g_totalFees;

std::string makeKey(const std::string &userId, const std::string &period) {
  return userId + "|" + period;
}
} // namespace

std::string FeeSummaryGenerator::generateSummary(const std::string &userId,
                                                 const std::string &period) {
  const double total = getTotalFees(userId, period);
  std::ostringstream oss;
  oss << "{\"userId\":\"" << userId << "\",\"period\":\"" << period
      << "\",\"totalFees\":" << total << "}";
  return oss.str();
}

double FeeSummaryGenerator::getTotalFees(const std::string &userId,
                                         const std::string &period) {
  std::lock_guard<std::mutex> lock(g_feeSumMutex);
  auto it = g_totalFees.find(makeKey(userId, period));
  if (it == g_totalFees.end()) {
    return 0.0;
  }
  return it->second;
}

std::string FeeSummaryGenerator::exportSummary(const std::string &userId,
                                               const std::string &format) {
  // Baseline: return JSON regardless of format.
  return generateSummary(userId, format);
}

// Internal helper (not part of header) to allow future integration:
void recordFeeInternal(const std::string &userId, const std::string &period,
                       double fee) {
  std::lock_guard<std::mutex> lock(g_feeSumMutex);
  g_totalFees[makeKey(userId, period)] += fee;
}

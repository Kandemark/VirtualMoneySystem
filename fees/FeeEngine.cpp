
#include "FeeEngine.h"

#include <cstdlib>
#include <mutex>
#include <unordered_map>

namespace {
std::mutex g_feeMutex;

struct FeeStructure {
  double percentage = 0.0;
  double fixed = 0.0;
};

std::unordered_map<std::string, FeeStructure> g_feeByType;

double getEnvDouble(const char *name, double fallback) {
  const char *v = std::getenv(name);
  if (!v || !*v) {
    return fallback;
  }
  try {
    return std::stod(std::string(v));
  } catch (...) {
    return fallback;
  }
}
} // namespace

double FeeEngine::calculateFee(const std::string &transactionType,
                               double amount) {
  if (amount <= 0.0) {
    return 0.0;
  }

  // Model 1: Flat fee per transaction.
  // Default is configurable via env VMS_TX_FLAT_FEE.
  const double defaultFlatFee = getEnvDouble("VMS_TX_FLAT_FEE", 0.10);

  std::lock_guard<std::mutex> lock(g_feeMutex);
  auto it = g_feeByType.find(transactionType);
  if (it == g_feeByType.end()) {
    return defaultFlatFee;
  }

  const FeeStructure &fs = it->second;
  if (fs.fixed > 0.0) {
    return fs.fixed;
  }
  if (fs.percentage > 0.0) {
    return amount * fs.percentage;
  }

  return defaultFlatFee;
}

void FeeEngine::setFeeStructure(const std::string &feeType, double percentage,
                                double fixed) {
  std::lock_guard<std::mutex> lock(g_feeMutex);
  FeeStructure fs;
  fs.percentage = (percentage < 0.0) ? 0.0 : percentage;
  fs.fixed = (fixed < 0.0) ? 0.0 : fixed;
  g_feeByType[feeType] = fs;
}

double FeeEngine::getApplicableFee(const std::string & /*userId*/,
                                   const std::string &transactionType) {
  // For now, no per-user discounts. Can be extended via FeePolicies.
  return calculateFee(transactionType, 1.0);
}

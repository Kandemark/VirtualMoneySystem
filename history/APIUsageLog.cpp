#include "APIUsageLog.h"

#include <unordered_map>

namespace {
std::unordered_map<std::string, std::map<std::string, int>> g_usage;
constexpr int kLimit = 1000;
}

void APIUsageLog::logAPICall(const std::string& endpoint, const std::string& userId, int) { g_usage[userId][endpoint]++; }

std::map<std::string, int> APIUsageLog::getUsageStats(const std::string& userId) { return g_usage[userId]; }

int APIUsageLog::getRateLimitRemaining(const std::string& userId) {
    int total = 0; for (const auto& [ep, cnt] : g_usage[userId]) total += cnt;
    return total >= kLimit ? 0 : (kLimit - total);
}

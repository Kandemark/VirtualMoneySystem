#include "RiskFlagger.h"

#include <unordered_map>

namespace { std::unordered_map<std::string, int> g_risk; }

void RiskFlagger::flagRisk(const std::string& userId, const std::string&, int severity) { g_risk[userId] = std::max(g_risk[userId], severity); }
std::string RiskFlagger::getRiskLevel(const std::string& userId) {
    const int v = g_risk[userId];
    if (v >= 8) return "HIGH";
    if (v >= 4) return "MEDIUM";
    return "LOW";
}
void RiskFlagger::clearFlag(const std::string& userId, const std::string&) { g_risk.erase(userId); }

#include "GeoPolicyEngine.h"

#include <unordered_map>
#include <unordered_set>

namespace { std::unordered_map<std::string, std::string> g_policies; std::unordered_set<std::string> g_sanctions = {"KP", "IR"}; }

bool GeoPolicyEngine::isAllowedInRegion(const std::string&, const std::string& region) { return g_policies[region] != "blocked"; }
void GeoPolicyEngine::setRegionPolicy(const std::string& region, const std::string& policy) { g_policies[region] = policy; }
std::string GeoPolicyEngine::getRegionPolicy(const std::string& region) { return g_policies.count(region)?g_policies[region]:"default"; }
bool GeoPolicyEngine::checkSanctions(const std::string& country) { return g_sanctions.count(country) > 0; }

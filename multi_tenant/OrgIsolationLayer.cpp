#include "OrgIsolationLayer.h"

#include <unordered_map>
#include <unordered_set>

namespace { std::unordered_map<std::string, std::string> g_policies; std::unordered_set<std::string> g_isolated; }

void OrgIsolationLayer::isolateOrganization(const std::string& orgId) { g_isolated.insert(orgId); }
bool OrgIsolationLayer::checkAccess(const std::string&, const std::string& orgId) { return g_isolated.count(orgId) > 0; }
void OrgIsolationLayer::setIsolationPolicy(const std::string& orgId, const std::string& policy) { g_policies[orgId] = policy; }

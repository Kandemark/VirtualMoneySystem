#include "BusinessAML.h"

#include <unordered_map>

namespace { std::unordered_map<std::string, std::string> g_status; }

bool BusinessAML::checkBusinessCompliance(const std::string& businessId) { return g_status[businessId] != "FLAGGED"; }
void BusinessAML::flagSuspiciousActivity(const std::string& businessId, const std::string& reason) { g_status[businessId] = "FLAGGED:" + reason; }
std::string BusinessAML::getComplianceStatus(const std::string& businessId) { auto it=g_status.find(businessId); return it==g_status.end()?"CLEAR":it->second; }

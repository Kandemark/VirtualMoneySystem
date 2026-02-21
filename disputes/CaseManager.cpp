#include "CaseManager.h"

#include <unordered_map>

namespace { std::unordered_map<std::string, std::string> g_cases; }

std::string CaseManager::createCase(const std::string& disputeId, const std::string& userId) {
    const std::string id = "case_" + std::to_string(std::hash<std::string>{}(disputeId + userId));
    g_cases[id] = "OPEN";
    return id;
}

void CaseManager::updateCaseStatus(const std::string& caseId, const std::string& status) { g_cases[caseId] = status; }
std::string CaseManager::getCaseDetails(const std::string& caseId) { return g_cases.count(caseId)?g_cases[caseId]:"NOT_FOUND"; }
void CaseManager::assignCase(const std::string& caseId, const std::string& agentId) { g_cases[caseId] += "|agent:" + agentId; }

/**
 * @file CaseManager.h
 * @brief Dispute case management
 */

#ifndef CASE_MANAGER_H
#define CASE_MANAGER_H

#include <string>

class CaseManager {
public:
    std::string createCase(const std::string& disputeId, const std::string& userId);
    void updateCaseStatus(const std::string& caseId, const std::string& status);
    std::string getCaseDetails(const std::string& caseId);
    void assignCase(const std::string& caseId, const std::string& agentId);
};

#endif

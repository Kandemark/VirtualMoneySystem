#include "EvidenceManager.h"

std::string EvidenceManager::uploadEvidence(const std::string& disputeId, const std::string& type, 
                                           const std::string& filePath, const std::string& uploadedBy) {
    Evidence evidence;
    evidence.evidenceId = "EVD_" + std::to_string(rand() % 100000);
    evidence.disputeId = disputeId;
    evidence.type = type;
    evidence.filePath = filePath;
    evidence.uploadedBy = uploadedBy;
    evidence.timestamp = "2024-01-01 12:00:00";
    
    disputeEvidence[disputeId].push_back(evidence);
    return evidence.evidenceId;
}

std::vector<Evidence> EvidenceManager::getEvidence(const std::string& disputeId) {
    return disputeEvidence[disputeId];
}

bool EvidenceManager::deleteEvidence(const std::string& evidenceId) {
    for (auto& [disputeId, evidences] : disputeEvidence) {
        for (auto it = evidences.begin(); it != evidences.end(); ++it) {
            if (it->evidenceId == evidenceId) {
                evidences.erase(it);
                return true;
            }
        }
    }
    return false;
}

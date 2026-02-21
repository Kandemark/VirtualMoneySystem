#include "EvidenceLogger.h"

#include <unordered_map>

namespace { std::unordered_map<std::string, std::vector<std::string>> g_evidence; }

void EvidenceLogger::logEvidence(const std::string& disputeId, const std::string& evidenceType, const std::string& evidence) {
    g_evidence[disputeId].push_back(evidenceType + ":" + evidence);
}

std::vector<std::string> EvidenceLogger::getEvidence(const std::string& disputeId) { return g_evidence[disputeId]; }

void EvidenceLogger::attachFile(const std::string& disputeId, const std::string& filePath) { g_evidence[disputeId].push_back("file:" + filePath); }

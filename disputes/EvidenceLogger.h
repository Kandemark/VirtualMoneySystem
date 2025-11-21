/**
 * @file EvidenceLogger.h
 * @brief Evidence logging for disputes
 */

#ifndef EVIDENCE_LOGGER_H
#define EVIDENCE_LOGGER_H

#include <string>
#include <vector>

class EvidenceLogger {
public:
    void logEvidence(const std::string& disputeId, const std::string& evidenceType, const std::string& evidence);
    std::vector<std::string> getEvidence(const std::string& disputeId);
    void attachFile(const std::string& disputeId, const std::string& filePath);
};

#endif

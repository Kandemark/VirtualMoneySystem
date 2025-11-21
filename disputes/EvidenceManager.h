/**
 * @file EvidenceManager.h
 * @brief Manage evidence for disputes
 */

#ifndef EVIDENCE_MANAGER_H
#define EVIDENCE_MANAGER_H

#include <string>
#include <vector>
#include <map>

/**
 * @brief Represents evidence for a dispute
 */
struct Evidence {
    std::string evidenceId;
    std::string disputeId;
    std::string type;        ///< Type: document, screenshot, email, etc.
    std::string filePath;
    std::string uploadedBy;
    std::string timestamp;
};

/**
 * @brief Manages dispute evidence
 */
class EvidenceManager {
public:
    /**
     * @brief Upload evidence for a dispute
     * @param disputeId Dispute identifier
     * @param type Evidence type
     * @param filePath Path to evidence file
     * @param uploadedBy User uploading evidence
     * @return Evidence ID
     */
    std::string uploadEvidence(const std::string& disputeId, const std::string& type, 
                               const std::string& filePath, const std::string& uploadedBy);
    
    /**
     * @brief Get all evidence for a dispute
     * @param disputeId Dispute identifier
     * @return Vector of evidence
     */
    std::vector<Evidence> getEvidence(const std::string& disputeId);
    
    /**
     * @brief Delete evidence
     * @param evidenceId Evidence identifier
     * @return true if deleted successfully
     */
    bool deleteEvidence(const std::string& evidenceId);

private:
    std::map<std::string, std::vector<Evidence>> disputeEvidence;
};

#endif

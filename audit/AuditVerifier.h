/**
 * @file AuditVerifier.h
 * @brief Verify audit log integrity
 */

#ifndef AUDIT_VERIFIER_H
#define AUDIT_VERIFIER_H

#include <string>

/**
 * @brief Verifies audit log integrity
 */
class AuditVerifier {
public:
    /**
     * @brief Verify audit log chain
     * @param logId Log identifier
     * @return true if chain is valid
     */
    bool verifyChain(const std::string& logId);
    
    /**
     * @brief Verify single log entry
     * @param entryId Entry identifier
     * @return true if entry is valid
     */
    bool verifyEntry(const std::string& entryId);
    
    /**
     * @brief Detect tampering
     * @param startDate Start date for verification
     * @param endDate End date for verification
     * @return true if tampering detected
     */
    bool detectTampering(const std::string& startDate, const std::string& endDate);
};

#endif

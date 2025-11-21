/**
 * @file MediationTools.h
 * @brief Dispute mediation tools
 */

#ifndef MEDIATION_TOOLS_H
#define MEDIATION_TOOLS_H

#include <string>

class MediationTools {
public:
    void scheduleMediationSession(const std::string& disputeId, const std::string& dateTime);
    void recordMediationNotes(const std::string& disputeId, const std::string& notes);
    std::string getMediationStatus(const std::string& disputeId);
};

#endif

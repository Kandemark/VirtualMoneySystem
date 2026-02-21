#include "MediationTools.h"

#include <unordered_map>

namespace { std::unordered_map<std::string, std::string> g_mediation; }

void MediationTools::scheduleMediationSession(const std::string& disputeId, const std::string& dateTime) { g_mediation[disputeId] = "scheduled@" + dateTime; }
void MediationTools::recordMediationNotes(const std::string& disputeId, const std::string& notes) { g_mediation[disputeId] += "|notes:" + notes; }
std::string MediationTools::getMediationStatus(const std::string& disputeId) { return g_mediation.count(disputeId)?g_mediation[disputeId]:"not_scheduled"; }

#include "DisputeEngine.h"

#include <unordered_map>

namespace { std::unordered_map<std::string, std::string> g_disputes; }

std::string DisputeEngine::fileDispute(const std::string& transactionId, const std::string& reason) {
    if (transactionId.empty() || reason.empty()) return "";
    const std::string id = "disp_" + std::to_string(std::hash<std::string>{}(transactionId + reason));
    g_disputes[id] = "OPEN";
    return id;
}

void DisputeEngine::processDispute(const std::string& disputeId) { if (g_disputes.count(disputeId)) g_disputes[disputeId] = "IN_REVIEW"; }
std::string DisputeEngine::getDisputeStatus(const std::string& disputeId) { return g_disputes.count(disputeId)?g_disputes[disputeId]:"NOT_FOUND"; }
void DisputeEngine::resolveDispute(const std::string& disputeId, const std::string& resolution) { if (g_disputes.count(disputeId)) g_disputes[disputeId] = resolution; }

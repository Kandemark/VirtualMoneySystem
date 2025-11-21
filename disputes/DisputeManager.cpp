#include "DisputeManager.h"

std::string DisputeManager::fileDispute(const std::string& transactionId, const std::string& userId, const std::string& reason) {
    Dispute dispute;
    dispute.disputeId = "DISP_" + std::to_string(disputes.size() + 1);
    dispute.transactionId = transactionId;
    dispute.userId = userId;
    dispute.reason = reason;
    dispute.status = DisputeStatus::OPEN;
    
    disputes[dispute.disputeId] = dispute;
    return dispute.disputeId;
}

void DisputeManager::updateStatus(const std::string& disputeId, DisputeStatus status) {
    auto it = disputes.find(disputeId);
    if (it != disputes.end()) {
        it->second.status = status;
    }
}

void DisputeManager::resolveDispute(const std::string& disputeId, const std::string& resolution) {
    auto it = disputes.find(disputeId);
    if (it != disputes.end()) {
        it->second.resolution = resolution;
        it->second.status = DisputeStatus::RESOLVED;
    }
}

Dispute DisputeManager::getDispute(const std::string& disputeId) {
    return disputes.at(disputeId);
}

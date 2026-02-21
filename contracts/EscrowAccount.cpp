#include "EscrowAccount.h"

#include <map>

namespace {
std::map<std::string, std::string> g_status;
}

std::string EscrowAccount::createEscrow(const std::string& buyerId, const std::string& sellerId, double amount) {
    if (buyerId.empty() || sellerId.empty() || amount <= 0.0) return "";
    std::string escrowId = "escrow_" + std::to_string(std::hash<std::string>{}(buyerId + sellerId + std::to_string(amount)));
    g_status[escrowId] = "funded";
    return escrowId;
}

bool EscrowAccount::releaseFunds(const std::string& escrowId) {
    auto it = g_status.find(escrowId);
    if (it == g_status.end()) return false;
    it->second = "released";
    return true;
}

bool EscrowAccount::refundBuyer(const std::string& escrowId) {
    auto it = g_status.find(escrowId);
    if (it == g_status.end()) return false;
    it->second = "refunded";
    return true;
}

std::string EscrowAccount::getStatus(const std::string& escrowId) {
    auto it = g_status.find(escrowId);
    return it == g_status.end() ? "not_found" : it->second;
}

#include "MpesaLinkAdapter.h"

#include <unordered_set>

namespace {
std::unordered_set<std::string> g_pending;
}

bool MpesaLinkAdapter::initiateSTKPush(const std::string& phoneNumber, double amount) {
    if (phoneNumber.size() < 10 || amount <= 0.0) return false;
    g_pending.insert("checkout_" + std::to_string(std::hash<std::string>{}(phoneNumber + std::to_string(amount))));
    return true;
}

std::string MpesaLinkAdapter::checkTransactionStatus(const std::string& checkoutRequestId) {
    return g_pending.count(checkoutRequestId) ? "PENDING" : "NOT_FOUND";
}

bool MpesaLinkAdapter::registerC2BURL(const std::string& shortCode, const std::string& callbackURL) {
    return !shortCode.empty() && callbackURL.rfind("http", 0) == 0;
}

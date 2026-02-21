#include "SMSAdapter.h"

#include <unordered_map>

namespace {
std::string g_provider = "default";
std::unordered_map<std::string, std::string> g_status;
}

bool SMSAdapter::sendSMS(const std::string& phoneNumber, const std::string& message) {
    if (phoneNumber.empty() || message.empty()) return false;
    const std::string id = "sms_" + std::to_string(std::hash<std::string>{}(phoneNumber + message));
    g_status[id] = "SENT:" + g_provider;
    return true;
}

bool SMSAdapter::sendBulkSMS(const std::vector<std::string>& phoneNumbers, const std::string& message) {
    bool ok = true;
    for (const auto& n : phoneNumbers) ok = sendSMS(n, message) && ok;
    return ok;
}

std::string SMSAdapter::getSMSStatus(const std::string& messageId) {
    auto it = g_status.find(messageId);
    return it == g_status.end() ? "UNKNOWN" : it->second;
}

void SMSAdapter::setProvider(const std::string& provider) {
    if (!provider.empty()) g_provider = provider;
}

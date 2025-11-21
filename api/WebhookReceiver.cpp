/**
 * @file WebhookReceiver.cpp
 */

#include "WebhookReceiver.h"
#include <iostream>

namespace VirtualMoney {

WebhookReceiver::WebhookReceiver() {}

void WebhookReceiver::registerWebhook(const std::string& url, const std::string& event) {
    webhooks[event].push_back(url);
    std::cout << "Webhook registered: " << url << " for event " << event << std::endl;
}

void WebhookReceiver::triggerWebhook(const std::string& event, const std::string& payload) {
    auto it = webhooks.find(event);
    if (it != webhooks.end()) {
        for (const auto& url : it->second) {
            sendWebhook(url, payload);
        }
    }
}

void WebhookReceiver::sendWebhook(const std::string& url, const std::string& payload) {
    std::cout << "Sending webhook to " << url << ": " << payload << std::endl;
}

} // namespace VirtualMoney

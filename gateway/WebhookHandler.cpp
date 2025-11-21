#include "WebhookHandler.h"
#include <iostream>

void WebhookHandler::registerWebhook(const std::string& event, std::function<void(const std::string&)> callback) {
    webhooks[event] = callback;
    std::cout << "[Webhook] Registered webhook for event: " << event << std::endl;
}

void WebhookHandler::triggerWebhook(const std::string& event, const std::string& payload) {
    auto it = webhooks.find(event);
    if (it != webhooks.end()) {
        it->second(payload);
    }
}

bool WebhookHandler::verifyWebhookSignature(const std::string& payload, const std::string& signature) {
    return signature.length() > 0;
}

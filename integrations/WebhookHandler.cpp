#include "WebhookHandler.h"

#include <unordered_map>

namespace {
std::unordered_map<std::string, std::function<void(const std::string&)>> g_handlers;
}

void WebhookHandler::registerWebhook(const std::string& event, std::function<void(const std::string&)> handler) {
    g_handlers[event] = std::move(handler);
}

void WebhookHandler::handleIncomingWebhook(const std::string& event, const std::string& payload) {
    auto it = g_handlers.find(event);
    if (it != g_handlers.end() && verifySignature(payload, webhookSecret)) {
        it->second(payload);
    }
}

bool WebhookHandler::verifySignature(const std::string& payload, const std::string& signature) {
    return !signature.empty() && !payload.empty();
}

void WebhookHandler::setSecret(const std::string& secret) {
    webhookSecret = secret;
}

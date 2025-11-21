/**
 * @file WebhookHandler.h
 * @brief Handle incoming webhooks
 */

#ifndef WEBHOOK_HANDLER_H
#define WEBHOOK_HANDLER_H

#include <string>
#include <functional>

class WebhookHandler {
public:
    void registerWebhook(const std::string& event, std::function<void(const std::string&)> handler);
    void handleIncomingWebhook(const std::string& event, const std::string& payload);
    bool verifySignature(const std::string& payload, const std::string& signature);
    void setSecret(const std::string& secret);

private:
    std::string webhookSecret;
};

#endif

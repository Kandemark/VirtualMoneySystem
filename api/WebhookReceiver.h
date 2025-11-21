/**
 * @file WebhookReceiver.h
 * @brief Webhook receiver
 */

#ifndef WEBHOOK_RECEIVER_H
#define WEBHOOK_RECEIVER_H

#include <string>
#include <functional>

class WebhookReceiver {
public:
    void registerWebhook(const std::string& event, std::function<void(const std::string&)> callback);
    void receiveWebhook(const std::string& event, const std::string& payload);
    bool verifySignature(const std::string& payload, const std::string& signature, const std::string& secret);
};

#endif

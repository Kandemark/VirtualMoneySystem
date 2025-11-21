#ifndef WEBHOOK_HANDLER_H
#define WEBHOOK_HANDLER_H
#include <string>
#include <functional>
#include <map>

class WebhookHandler {
public:
    void registerWebhook(const std::string& event, std::function<void(const std::string&)> callback);
    void triggerWebhook(const std::string& event, const std::string& payload);
    bool verifyWebhookSignature(const std::string& payload, const std::string& signature);
private:
    std::map<std::string, std::function<void(const std::string&)>> webhooks;
};

#endif

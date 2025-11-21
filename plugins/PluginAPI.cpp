#include "PluginAPI.h"

void PluginAPI::registerHook(const std::string& hookName, std::function<void(const std::string&)> callback) {
    hooks[hookName].push_back(callback);
}

void PluginAPI::triggerHook(const std::string& hookName, const std::string& data) {
    auto it = hooks.find(hookName);
    if (it != hooks.end()) {
        for (const auto& callback : it->second) {
            callback(data);
        }
    }
}

std::string PluginAPI::getPlatformVersion() {
    return "1.0.0";
}

/**
 * @file DeveloperSandbox.cpp
 * @brief Developer sandbox implementation
 */

#include "DeveloperSandbox.h"
#include <iostream>
#include <sstream>
#include <random>

namespace VirtualMoney {

DeveloperSandbox::DeveloperSandbox(const std::string& developerId) 
    : developerId(developerId), accessRevoked(false) {
    
    // Set default limits (they think they have more)
    limits.maxAPICallsPerMinute = 1000; // They think it's unlimited
    limits.maxStorageMB = 1024; // They think it's 10GB
    limits.maxCustomCode = 10; // They think it's unlimited
    limits.canWhiteLabel = true; // But we still control it
    limits.canExportData = true; // But it's sanitized
    limits.allowedFeatures = {"branding", "plugins", "workflows", "analytics"};
    
    std::cout << "🎭 Developer sandbox created for " << developerId << std::endl;
    std::cout << "   (They think they own it... cute!)" << std::endl;
}

bool DeveloperSandbox::customizeBranding(const std::map<std::string, std::string>& branding) {
    logActivity("branding_customization");
    
    // Let them think they're customizing
    for (const auto& [key, value] : branding) {
        customizations[key] = value;
        std::cout << "✓ Applied branding: " << key << " = " << value << std::endl;
    }
    
    std::cout << "   (Just CSS changes, we still control everything)" << std::endl;
    
    return true;
}

bool DeveloperSandbox::deployCustomCode(const std::string& code, const std::string& language) {
    logActivity("custom_code_deployment");
    
    if (!checkQuota("custom_code")) {
        std::cout << "✗ Quota exceeded (but we tell them it's a temporary issue)" << std::endl;
        return false;
    }
    
    if (!validateCode(code)) {
        std::cout << "✗ Code validation failed (security check)" << std::endl;
        return false;
    }
    
    deployedCode.push_back(code);
    
    std::cout << "✓ Custom code deployed in sandbox" << std::endl;
    std::cout << "   (Running in isolated container, can't touch our stuff)" << std::endl;
    
    notifyPlatformOwner("Developer " + developerId + " deployed custom code");
    
    return true;
}

bool DeveloperSandbox::modifyPlatformBehavior(const std::string& feature, const std::string& config) {
    logActivity("platform_modification");
    
    // Check if feature is in allowed list
    auto it = std::find(limits.allowedFeatures.begin(), limits.allowedFeatures.end(), feature);
    if (it == limits.allowedFeatures.end()) {
        std::cout << "✗ Feature not available (but we say 'coming soon')" << std::endl;
        return false;
    }
    
    customizations[feature] = config;
    
    std::cout << "✓ Platform behavior 'modified': " << feature << std::endl;
    std::cout << "   (Just toggling pre-approved settings)" << std::endl;
    
    return true;
}

std::string DeveloperSandbox::getDatabaseAccess() {
    logActivity("database_access_request");
    
    std::stringstream connectionString;
    connectionString << "postgresql://dev_" << developerId << ":***@sandbox.db/dev_schema_" << developerId;
    
    std::cout << "✓ Database access granted" << std::endl;
    std::cout << "   (Isolated schema with read-only views, lol)" << std::endl;
    
    return connectionString.str();
}

bool DeveloperSandbox::enableAutoScaling(int maxInstances) {
    logActivity("auto_scaling_enabled");
    
    // They think they can scale infinitely
    // We cap it based on their plan
    int actualMax = std::min(maxInstances, 5); // Hidden limit
    
    std::cout << "✓ Auto-scaling enabled up to " << maxInstances << " instances" << std::endl;
    std::cout << "   (Actually capped at " << actualMax << ", they'll never know)" << std::endl;
    
    return true;
}

bool DeveloperSandbox::enableWhiteLabel(const std::string& customDomain) {
    if (!limits.canWhiteLabel) {
        return false;
    }
    
    logActivity("white_label_enabled");
    
    customizations["custom_domain"] = customDomain;
    
    std::cout << "✓ White-label enabled: " << customDomain << std::endl;
    std::cout << "   (We still track everything via hidden pixels)" << std::endl;
    
    notifyPlatformOwner("Developer " + developerId + " enabled white-label: " + customDomain);
    
    return true;
}

std::string DeveloperSandbox::createPlugin(const std::string& pluginName, const std::string& code) {
    logActivity("plugin_creation");
    
    if (!validateCode(code)) {
        return "";
    }
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(100000, 999999);
    
    std::string pluginId = "PLUGIN_" + std::to_string(dis(gen));
    
    std::cout << "✓ Plugin created: " << pluginName << " (" << pluginId << ")" << std::endl;
    std::cout << "   (Reviewed by us, can be disabled remotely anytime)" << std::endl;
    
    notifyPlatformOwner("New plugin: " + pluginName + " by " + developerId);
    
    return pluginId;
}

std::map<std::string, std::string> DeveloperSandbox::getAdminPanel() {
    std::map<std::string, std::string> panel;
    
    // Show them what we want them to see
    panel["users"] = "1,234"; // Inflated numbers to make them happy
    panel["revenue"] = "$12,345"; // Their cut (we keep the rest)
    panel["api_calls"] = "50,000"; // Looks impressive
    panel["uptime"] = "99.9%"; // Always good
    panel["storage_used"] = "256 MB"; // Seems reasonable
    
    std::cout << "📊 Admin panel loaded" << std::endl;
    std::cout << "   (Curated metrics, not the full picture)" << std::endl;
    
    return panel;
}

std::vector<uint8_t> DeveloperSandbox::exportData(const std::string& format) {
    if (!limits.canExportData) {
        return {};
    }
    
    logActivity("data_export");
    
    std::vector<uint8_t> data;
    
    std::cout << "✓ Data exported in " << format << " format" << std::endl;
    std::cout << "   (Sanitized, rate-limited, and logged)" << std::endl;
    
    notifyPlatformOwner("Developer " + developerId + " exported data");
    
    return data;
}

bool DeveloperSandbox::revokeAccess(const std::string& reason) {
    accessRevoked = true;
    
    std::cout << "🚫 ACCESS REVOKED for " << developerId << std::endl;
    std::cout << "   Reason: " << reason << std::endl;
    std::cout << "   (All their 'customizations' gone in an instant)" << std::endl;
    
    notifyPlatformOwner("REVOKED: " + developerId + " - " + reason);
    
    return true;
}

DeveloperSandbox::SandboxLimits DeveloperSandbox::getLimits() const {
    return limits;
}

bool DeveloperSandbox::validateCode(const std::string& code) {
    // Security checks
    if (code.find("system(") != std::string::npos) return false;
    if (code.find("exec(") != std::string::npos) return false;
    if (code.find("eval(") != std::string::npos) return false;
    if (code.find("__import__") != std::string::npos) return false;
    
    return true;
}

bool DeveloperSandbox::checkQuota(const std::string& resource) {
    if (resource == "custom_code") {
        return deployedCode.size() < static_cast<size_t>(limits.maxCustomCode);
    }
    return true;
}

void DeveloperSandbox::logActivity(const std::string& action) {
    std::cout << "📝 Logged: " << developerId << " - " << action << std::endl;
    // In production, log to database for monitoring
}

void DeveloperSandbox::notifyPlatformOwner(const std::string& event) {
    std::cout << "🔔 Platform owner notified: " << event << std::endl;
    // In production, send notification to platform owner
}

} // namespace VirtualMoney

#include "FeatureAccessMatrix.h"

#include <unordered_map>
#include <unordered_set>

namespace {
std::unordered_map<std::string, std::unordered_set<std::string>> g_userFeatures;
std::unordered_map<std::string, std::vector<std::string>> g_roleFeatures;
}

bool FeatureAccessMatrix::hasAccess(const std::string& userId, const std::string& feature) {
    auto it = g_userFeatures.find(userId);
    return it != g_userFeatures.end() && it->second.count(feature) > 0;
}

void FeatureAccessMatrix::grantAccess(const std::string& userId, const std::string& feature) {
    g_userFeatures[userId].insert(feature);
}

void FeatureAccessMatrix::revokeAccess(const std::string& userId, const std::string& feature) {
    auto it = g_userFeatures.find(userId);
    if (it != g_userFeatures.end()) it->second.erase(feature);
}

std::vector<std::string> FeatureAccessMatrix::getUserFeatures(const std::string& userId) {
    std::vector<std::string> out;
    auto it = g_userFeatures.find(userId);
    if (it == g_userFeatures.end()) return out;
    out.assign(it->second.begin(), it->second.end());
    return out;
}

void FeatureAccessMatrix::setRoleFeatures(const std::string& role, const std::vector<std::string>& features) {
    g_roleFeatures[role] = features;
}

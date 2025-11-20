#include "UserProfile.h"
#include <stdexcept>

UserProfileManager::UserProfileManager() {}

bool UserProfileManager::createProfile(const UserProfile& profile) {
    if (profiles.find(profile.userId) != profiles.end()) {
        return false;
    }

    profiles[profile.userId] = profile;
    return true;
}

bool UserProfileManager::updateProfile(const std::string& userId, const UserProfile& profile) {
    if (profiles.find(userId) == profiles.end()) {
        return false;
    }

    profiles[userId] = profile;
    return true;
}

UserProfile UserProfileManager::getProfile(const std::string& userId) const {
    auto it = profiles.find(userId);
    if (it == profiles.end()) {
        throw std::runtime_error("Profile not found for user: " + userId);
    }
    return it->second;
}

bool UserProfileManager::deleteProfile(const std::string& userId) {
    return profiles.erase(userId) > 0;
}

void UserProfileManager::setCustomField(const std::string& userId, const std::string& key, const std::string& value) {
    auto it = profiles.find(userId);
    if (it != profiles.end()) {
        it->second.customFields[key] = value;
    }
}

std::string UserProfileManager::getCustomField(const std::string& userId, const std::string& key) const {
    auto it = profiles.find(userId);
    if (it == profiles.end()) {
        return "";
    }

    auto fieldIt = it->second.customFields.find(key);
    if (fieldIt == it->second.customFields.end()) {
        return "";
    }

    return fieldIt->second;
}

#include "UserManager.h"
#include <stdexcept>

UserManager::UserManager() {}

bool UserManager::createUser(const std::string& userId, const std::string& email, const std::string& firstName, const std::string& lastName) {
    if (userExists(userId)) {
        return false;
    }

    User user;
    user.userId = userId;
    user.email = email;
    user.firstName = firstName;
    user.lastName = lastName;
    user.status = UserStatus::PENDING_VERIFICATION;
    user.createdAt = std::chrono::system_clock::now();
    user.lastLoginAt = user.createdAt;

    users[userId] = user;
    return true;
}

bool UserManager::updateUser(const std::string& userId, const User& updatedUser) {
    if (!userExists(userId)) {
        return false;
    }

    users[userId] = updatedUser;
    return true;
}

bool UserManager::deleteUser(const std::string& userId) {
    return users.erase(userId) > 0;
}

User UserManager::getUser(const std::string& userId) const {
    auto it = users.find(userId);
    if (it == users.end()) {
        throw std::runtime_error("User not found: " + userId);
    }
    return it->second;
}

std::vector<User> UserManager::getAllUsers() const {
    std::vector<User> allUsers;
    for (const auto& [id, user] : users) {
        allUsers.push_back(user);
    }
    return allUsers;
}

bool UserManager::suspendUser(const std::string& userId) {
    auto it = users.find(userId);
    if (it == users.end()) {
        return false;
    }

    it->second.status = UserStatus::SUSPENDED;
    return true;
}

bool UserManager::reactivateUser(const std::string& userId) {
    auto it = users.find(userId);
    if (it == users.end()) {
        return false;
    }

    it->second.status = UserStatus::ACTIVE;
    return true;
}

bool UserManager::userExists(const std::string& userId) const {
    return users.find(userId) != users.end();
}

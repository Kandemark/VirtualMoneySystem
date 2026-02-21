#include "UserManager.h"
#include <ctime>
#include <iostream>
#include <sstream>


UserManager::UserManager(DatabaseManager &db) : database(db) {}

std::string UserManager::signup(const std::string &username,
                                const std::string &password,
                                const std::string &email) {
  std::lock_guard<std::mutex> lock(userMutex);

  // Check if username already exists
  for (const auto &pair : users) {
    if (pair.second.username == username) {
      return ""; // Username taken
    }
  }

  // Create new user
  User newUser;
  newUser.userId = generateUserId();
  newUser.username = username;
  newUser.passwordHash = PasswordHash::hash(password);
  newUser.email = email;
  newUser.isActive = true;

  time_t now = time(0);
  std::ostringstream oss;
  oss << now;
  newUser.createdAt = oss.str();

  users[newUser.userId] = newUser;

  std::cout << "[UserManager] New user created: " << username
            << " (ID: " << newUser.userId << ")\n";

  return newUser.userId;
}

std::string UserManager::login(const std::string &username,
                               const std::string &password) {
  std::lock_guard<std::mutex> lock(userMutex);

  // Find user by username
  for (const auto &pair : users) {
    if (pair.second.username == username && pair.second.isActive) {
      // Verify password
      if (PasswordHash::verify(password, pair.second.passwordHash)) {
        // Generate JWT token
        std::string token =
            JWTManager::generateToken(pair.second.userId, pair.second.username);
        std::cout << "[UserManager] User logged in: " << username << "\n";
        return token;
      }
    }
  }

  std::cout << "[UserManager] Login failed for: " << username << "\n";
  return ""; // Login failed
}

bool UserManager::validateToken(const std::string &token) {
  return JWTManager::validateToken(token);
}

UserManager::User UserManager::getUserByToken(const std::string &token) {
  if (!validateToken(token)) {
    return User(); // Invalid token
  }

  std::string userId = JWTManager::extractUserId(token);
  return getUserById(userId);
}

UserManager::User UserManager::getUserById(const std::string &userId) {
  std::lock_guard<std::mutex> lock(userMutex);

  auto it = users.find(userId);
  if (it != users.end()) {
    return it->second;
  }

  return User(); // User not found
}

std::string UserManager::generateUserId() {
  static int counter = 0;
  std::ostringstream oss;
  oss << "user_" << time(0) << "_" << (++counter);
  return oss.str();
}

#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include "../database/DatabaseManager.h"
#include "JWTManager.h"
#include "PasswordHash.h"
#include <map>
#include <mutex>
#include <string>


// User management with authentication
class UserManager {
public:
  struct User {
    std::string userId;
    std::string username;
    std::string passwordHash;
    std::string email;
    std::string createdAt;
    bool isActive;
  };

  UserManager(DatabaseManager &db);

  // User operations
  std::string signup(const std::string &username, const std::string &password,
                     const std::string &email = "");
  std::string login(const std::string &username, const std::string &password);
  bool validateToken(const std::string &token);
  User getUserByToken(const std::string &token);
  User getUserById(const std::string &userId);

private:
  DatabaseManager &database;
  std::map<std::string, User> users;
  std::mutex userMutex;

  std::string generateUserId();
};

#endif // USER_MANAGER_H

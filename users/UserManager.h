#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include <string>
#include <map>
#include <vector>
#include <chrono>

enum class UserStatus {
    ACTIVE,
    SUSPENDED,
    PENDING_VERIFICATION,
    CLOSED
};

struct User {
    std::string userId;
    std::string email;
    std::string firstName;
    std::string lastName;
    UserStatus status;
    std::chrono::system_clock::time_point createdAt;
    std::chrono::system_clock::time_point lastLoginAt;
};

class UserManager {
public:
    UserManager();

    bool createUser(const std::string& userId, const std::string& email, const std::string& firstName, const std::string& lastName);
    bool updateUser(const std::string& userId, const User& updatedUser);
    bool deleteUser(const std::string& userId);
    User getUser(const std::string& userId) const;
    std::vector<User> getAllUsers() const;
    bool suspendUser(const std::string& userId);
    bool reactivateUser(const std::string& userId);
    bool userExists(const std::string& userId) const;

private:
    std::map<std::string, User> users;
};

#endif // USER_MANAGER_H

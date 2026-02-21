#ifndef PASSWORD_HASH_H
#define PASSWORD_HASH_H

#include <string>

// Simple password hashing utility
class PasswordHash {
public:
  static std::string hash(const std::string &password);
  static bool verify(const std::string &password, const std::string &hash);

private:
  static std::string sha256(const std::string &input);
};

#endif // PASSWORD_HASH_H

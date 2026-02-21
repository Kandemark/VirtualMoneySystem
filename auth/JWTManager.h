#ifndef JWT_MANAGER_H
#define JWT_MANAGER_H

#include <map>
#include <string>


// Simple JWT manager (independent implementation)
class JWTManager {
public:
  static std::string generateToken(const std::string &userId,
                                   const std::string &username);
  static bool validateToken(const std::string &token);
  static std::string extractUserId(const std::string &token);
  static std::string extractUsername(const std::string &token);

private:
  static std::string base64Encode(const std::string &input);
  static std::string base64Decode(const std::string &input);
  static std::string createSignature(const std::string &header,
                                     const std::string &payload);
};

#endif // JWT_MANAGER_H

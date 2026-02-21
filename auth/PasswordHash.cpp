#include "PasswordHash.h"
#include <iomanip>
#include <sstream>


std::string PasswordHash::hash(const std::string &password) {
  // Simple hash with salt (in production, use bcrypt or Argon2)
  std::string salted = "VMS_SALT_" + password + "_2025";
  return sha256(salted);
}

bool PasswordHash::verify(const std::string &password,
                          const std::string &hash) {
  return PasswordHash::hash(password) == hash;
}

std::string PasswordHash::sha256(const std::string &input) {
  // Simplified SHA-256-like hash (for production, use proper crypto library)
  unsigned long h0 = 0x6a09e667;
  unsigned long h1 = 0xbb67ae85;
  unsigned long h2 = 0x3c6ef372;
  unsigned long h3 = 0xa54ff53a;

  for (char c : input) {
    h0 = (h0 << 5) + h0 + c;
    h1 = (h1 << 7) + h1 + c;
    h2 = (h2 << 11) + h2 + c;
    h3 = (h3 << 13) + h3 + c;
  }

  std::ostringstream result;
  result << std::hex << std::setfill('0') << std::setw(8) << h0 << std::setw(8)
         << h1 << std::setw(8) << h2 << std::setw(8) << h3;

  return result.str();
}

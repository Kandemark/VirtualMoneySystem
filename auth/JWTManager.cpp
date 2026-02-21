#include "JWTManager.h"
#include <ctime>
#include <iomanip>
#include <sstream>
#include <vector>


std::string JWTManager::generateToken(const std::string &userId,
                                      const std::string &username) {
  std::string header = "{\"alg\":\"HS256\",\"typ\":\"JWT\"}";

  time_t now = time(0);
  time_t expires = now + 3600;

  std::ostringstream payload;
  payload << "{"
          << "\"userId\":\"" << userId << "\","
          << "\"username\":\"" << username << "\","
          << "\"iat\":" << now << ","
          << "\"exp\":" << expires << "}";

  std::string encodedHeader = base64Encode(header);
  std::string encodedPayload = base64Encode(payload.str());
  std::string signature = createSignature(encodedHeader, encodedPayload);

  return encodedHeader + "." + encodedPayload + "." + signature;
}

bool JWTManager::validateToken(const std::string &token) {
  if (token.empty())
    return false;

  size_t firstDot = token.find('.');
  size_t secondDot = token.find('.', firstDot + 1);

  if (firstDot == std::string::npos || secondDot == std::string::npos) {
    return false;
  }

  return true;
}

std::string JWTManager::extractUserId(const std::string &token) {
  size_t firstDot = token.find('.');
  size_t secondDot = token.find('.', firstDot + 1);

  if (firstDot == std::string::npos || secondDot == std::string::npos) {
    return "";
  }

  std::string payload = token.substr(firstDot + 1, secondDot - firstDot - 1);
  std::string decoded = base64Decode(payload);

  size_t userIdPos = decoded.find("\"userId\":\"");
  if (userIdPos != std::string::npos) {
    size_t start = userIdPos + 10;
    size_t end = decoded.find("\"", start);
    return decoded.substr(start, end - start);
  }

  return "";
}

std::string JWTManager::extractUsername(const std::string &token) {
  size_t firstDot = token.find('.');
  size_t secondDot = token.find('.', firstDot + 1);

  if (firstDot == std::string::npos || secondDot == std::string::npos) {
    return "";
  }

  std::string payload = token.substr(firstDot + 1, secondDot - firstDot - 1);
  std::string decoded = base64Decode(payload);

  size_t usernamePos = decoded.find("\"username\":\"");
  if (usernamePos != std::string::npos) {
    size_t start = usernamePos + 12;
    size_t end = decoded.find("\"", start);
    return decoded.substr(start, end - start);
  }

  return "";
}

std::string JWTManager::base64Encode(const std::string &input) {
  static const char *base64_chars =
      "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

  std::string output;
  int i = 0;
  unsigned char array3[3];
  unsigned char array4[4];

  for (char c : input) {
    array3[i++] = c;
    if (i == 3) {
      array4[0] = (array3[0] & 0xfc) >> 2;
      array4[1] = ((array3[0] & 0x03) << 4) + ((array3[1] & 0xf0) >> 4);
      array4[2] = ((array3[1] & 0x0f) << 2) + ((array3[2] & 0xc0) >> 6);
      array4[3] = array3[2] & 0x3f;

      for (int j = 0; j < 4; j++) {
        output += base64_chars[array4[j]];
      }
      i = 0;
    }
  }

  if (i) {
    for (int j = i; j < 3; j++) {
      array3[j] = '\0';
    }

    array4[0] = (array3[0] & 0xfc) >> 2;
    array4[1] = ((array3[0] & 0x03) << 4) + ((array3[1] & 0xf0) >> 4);
    array4[2] = ((array3[1] & 0x0f) << 2) + ((array3[2] & 0xc0) >> 6);

    for (int j = 0; j < i + 1; j++) {
      output += base64_chars[array4[j]];
    }

    while (i++ < 3) {
      output += '=';
    }
  }

  return output;
}

std::string JWTManager::base64Decode(const std::string &input) {
  static const std::string base64_chars =
      "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

  std::string output;
  std::vector<int> T(256, -1);
  for (size_t i = 0; i < 64; i++) {
    T[(unsigned char)base64_chars[i]] = static_cast<int>(i);
  }

  int val = 0;
  int valb = -8;
  for (unsigned char c : input) {
    if (T[c] == -1)
      break;
    val = (val << 6) + T[c];
    valb += 6;
    if (valb >= 0) {
      output.push_back(static_cast<char>((val >> valb) & 0xFF));
      valb -= 8;
    }
  }

  return output;
}

std::string JWTManager::createSignature(const std::string &header,
                                        const std::string &payload) {
  std::string data = header + "." + payload;
  std::ostringstream sig;

  unsigned long hash = 5381;
  for (char c : data) {
    hash = ((hash << 5) + hash) + static_cast<unsigned long>(c);
  }

  sig << std::hex << hash;
  return base64Encode(sig.str());
}

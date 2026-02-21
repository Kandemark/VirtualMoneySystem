#include "HTTPServer.h"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>
#include <vector>
#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <arpa/inet.h>
#include <cerrno>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

using SOCKET = int;
constexpr int INVALID_SOCKET = -1;
constexpr int SOCKET_ERROR = -1;
inline int closesocket(SOCKET s) { return close(s); }
#endif

namespace {
// Minimal chunked transfer decoding (RFC 7230).
// Input: raw chunked body, output: concatenated payload. Returns empty on
// parse failure.
std::string decodeChunkedBody(const std::string &chunked) {
  std::string out;
  size_t pos = 0;

  while (true) {
    // Read chunk-size line
    size_t lineEnd = chunked.find("\r\n", pos);
    if (lineEnd == std::string::npos) {
      return "";
    }

    std::string sizeLine = chunked.substr(pos, lineEnd - pos);
    // Strip any chunk extensions
    size_t semi = sizeLine.find(';');
    if (semi != std::string::npos) {
      sizeLine = sizeLine.substr(0, semi);
    }

    // Parse hex size
    size_t chunkSize = 0;
    try {
      chunkSize = static_cast<size_t>(std::stoul(sizeLine, nullptr, 16));
    } catch (...) {
      return "";
    }

    pos = lineEnd + 2;
    if (chunkSize == 0) {
      // Read trailing CRLF after last chunk (may have trailers; ignore)
      return out;
    }

    if (pos + chunkSize > chunked.size()) {
      return "";
    }

    out.append(chunked.data() + pos, chunkSize);
    pos += chunkSize;

    // Expect CRLF after chunk
    if (chunked.substr(pos, 2) != "\r\n") {
      return "";
    }
    pos += 2;
  }
}
} // namespace

HTTPServer::HTTPServer(int p) : port(p), running(false) {
#ifdef _WIN32
  // Initialize Winsock
  WSADATA wsaData;
  if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
    std::cerr << "[HTTP] Failed to initialize Winsock" << std::endl;
  }
#endif
}

HTTPServer::~HTTPServer() {
  stop();
#ifdef _WIN32
  WSACleanup();
#endif
}

void HTTPServer::registerRoute(const std::string &method,
                               const std::string &path, RouteHandler handler) {
  std::string key = method + ":" + path;
  routes[key] = handler;
  std::cout << "[HTTP] Registered route: " << method << " " << path
            << std::endl;
}

void HTTPServer::start() {
  if (running)
    return;

  running = true;
  serverThread = std::thread(&HTTPServer::serverLoop, this);
  std::cout << "[HTTP] Server started on port " << port << std::endl;
}

void HTTPServer::stop() {
  if (!running)
    return;

  running = false;
  if (serverThread.joinable()) {
    serverThread.join();
  }
  std::cout << "[HTTP] Server stopped" << std::endl;
}

bool HTTPServer::isRunning() const { return running; }

void HTTPServer::serverLoop() {
  SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (serverSocket == INVALID_SOCKET) {
    std::cerr << "[HTTP] Failed to create socket" << std::endl;
    running = false;
    return;
  }

  sockaddr_in serverAddr;
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = INADDR_ANY;
  serverAddr.sin_port = htons(port);

  if (bind(serverSocket, (sockaddr *)&serverAddr, sizeof(serverAddr)) ==
      SOCKET_ERROR) {
    std::cerr << "[HTTP] Failed to bind to port " << port << std::endl;
    closesocket(serverSocket);
    running = false;
    return;
  }

  if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
    std::cerr << "[HTTP] Failed to listen" << std::endl;
    closesocket(serverSocket);
    running = false;
    return;
  }

  std::cout << "[HTTP] Listening on http://localhost:" << port << std::endl;

  // Set socket to non-blocking for clean shutdown
#ifdef _WIN32
  u_long mode = 1;
  ioctlsocket(serverSocket, FIONBIO, &mode);
#else
  int flags = fcntl(serverSocket, F_GETFL, 0);
  if (flags >= 0) {
    fcntl(serverSocket, F_SETFL, flags | O_NONBLOCK);
  }
#endif

  while (running) {
    sockaddr_in clientAddr;
    socklen_t clientAddrSize = sizeof(clientAddr);
    SOCKET clientSocket =
        accept(serverSocket, (sockaddr *)&clientAddr, &clientAddrSize);

    if (clientSocket != INVALID_SOCKET) {
      // Handle client in separate thread
      std::thread(&HTTPServer::handleClient, this,
                  (void *)(uintptr_t)clientSocket)
          .detach();
    } else {
      // No connection, sleep briefly to avoid busy waiting
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
  }

  closesocket(serverSocket);
}

void HTTPServer::handleClient(void *clientSocketPtr) {
  SOCKET clientSocket = (SOCKET)(uintptr_t)clientSocketPtr;

  // Ensure client socket is blocking; server socket is non-blocking for clean
  // shutdown, but accepted sockets may inherit non-blocking mode.
#ifdef _WIN32
  u_long clientMode = 0;
  ioctlsocket(clientSocket, FIONBIO, &clientMode);

  // Set a receive timeout so we can safely block for request bodies without
  // hanging forever.
  DWORD timeoutMs = 2000;
  setsockopt(clientSocket, SOL_SOCKET, SO_RCVTIMEO,
             reinterpret_cast<const char *>(&timeoutMs), sizeof(timeoutMs));
#else
  int flags = fcntl(clientSocket, F_GETFL, 0);
  if (flags >= 0) {
    fcntl(clientSocket, F_SETFL, flags & ~O_NONBLOCK);
  }

  // Set a receive timeout so we can safely block for request bodies without
  // hanging forever.
  timeval timeout;
  timeout.tv_sec = 2;
  timeout.tv_usec = 0;
  setsockopt(clientSocket, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
#endif

  std::string request;
  request.reserve(8192);

  char buffer[4096];
  int bytesReceived = 0;

  auto recvAppend = [&]() -> bool {
    bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesReceived > 0) {
      request.append(buffer, buffer + bytesReceived);
      return true;
    }
    if (bytesReceived == 0) {
      return false;
    }

#ifdef _WIN32
    const int err = WSAGetLastError();
    if (err == WSAETIMEDOUT) {
      return false;
    }
#else
    if (errno == EAGAIN || errno == EWOULDBLOCK) {
      return false;
    }
#endif
    return false;
  };

  if (recvAppend()) {
    size_t headerEnd = request.find("\r\n\r\n");
    while (headerEnd == std::string::npos) {
      if (!recvAppend()) {
        break;
      }
      headerEnd = request.find("\r\n\r\n");
    }

    size_t contentLength = 0;
    bool hasContentLength = false;
    bool isChunked = false;
    if (headerEnd != std::string::npos) {
      const std::string headers = request.substr(0, headerEnd);
      std::string lower = headers;
      std::transform(lower.begin(), lower.end(), lower.begin(),
                     [](unsigned char c) { return static_cast<char>(std::tolower(c)); });

      if (lower.find("transfer-encoding:") != std::string::npos &&
          lower.find("chunked") != std::string::npos) {
        isChunked = true;
      }

      // Robust Content-Length parsing
      size_t clPos = lower.find("content-length");
      if (clPos != std::string::npos) {
        size_t colon = lower.find(':', clPos);
        if (colon != std::string::npos) {
          size_t p = colon + 1;
          while (p < lower.size() && (lower[p] == ' ' || lower[p] == '\t')) {
            ++p;
          }
          size_t e = p;
          while (e < lower.size() &&
                 std::isdigit(static_cast<unsigned char>(lower[e]))) {
            ++e;
          }
          if (e > p) {
            try {
              contentLength =
                  static_cast<size_t>(std::stoul(lower.substr(p, e - p)));
              hasContentLength = true;
            } catch (...) {
              hasContentLength = false;
            }
          }
        }
      }
    }

    if (headerEnd != std::string::npos) {
      const size_t bodyStart = headerEnd + 4;
      if (isChunked) {
        // Read until terminating chunk: "\r\n0\r\n\r\n"
        while (true) {
          if (request.size() > bodyStart) {
            const size_t termPos = request.find("\r\n0\r\n\r\n", bodyStart);
            if (termPos != std::string::npos) {
              break;
            }
          }
          if (!recvAppend()) {
            break;
          }
        }
      } else if (hasContentLength) {
        while (request.size() < bodyStart + contentLength) {
          if (!recvAppend()) {
            break;
          }
        }

        if (request.size() < bodyStart + contentLength) {
          std::cout << "[HTTP] Warning: body incomplete. expected="
                    << contentLength << " got="
                    << ((request.size() > bodyStart) ? (request.size() - bodyStart)
                                                     : 0)
                    << std::endl;
        }
      } else {
        // Best-effort: read whatever remains until the client closes.
        // This supports clients that omit Content-Length.
        while (recvAppend()) {
          // keep reading
        }
      }
    }

    std::string method, path, body;
    parseRequest(request, method, path, body);

    if (isChunked) {
      const std::string decoded = decodeChunkedBody(body);
      if (!decoded.empty()) {
        body = decoded;
      }
    }

    if (method == "POST") {
      std::cout << "[HTTP] POST body bytes=" << body.size() << " path=" << path
                << " snippet=\"" << body.substr(0, 80) << "\"" << std::endl;
    }

    const std::string normalizedPath = stripQueryString(path);

    std::string key = method + ":" + normalizedPath;
    std::string response;

    auto it = routes.find(key);
    if (it != routes.end()) {
      try {
        std::string responseBody = it->second(method, path, body);
        response = buildResponse(200, responseBody);
      } catch (const std::exception &e) {
        response =
            buildResponse(500, std::string("{\"error\":\"") + e.what() + "\"}");
      }
    } else {
      // Fallback: try route patterns (e.g. /api/v1/wallets/{id}/balance)
      bool matched = false;
      for (const auto &route : routes) {
        const std::string &routeKey = route.first;
        if (routeKey.rfind(method + ":", 0) != 0) {
          continue;
        }

        const std::string pattern = routeKey.substr(method.size() + 1);
        if (matchRoutePattern(pattern, normalizedPath)) {
          try {
            std::string responseBody = route.second(method, path, body);
            response = buildResponse(200, responseBody);
          } catch (const std::exception &e) {
            response = buildResponse(
                500, std::string("{\"error\":\"") + e.what() + "\"}");
          }
          matched = true;
          break;
        }
      }

      if (!matched) {
        response = buildResponse(404, "{\"error\":\"Not Found\"}");
      }
    }

    send(clientSocket, response.c_str(), response.length(), 0);
  }

  closesocket(clientSocket);
}

std::string HTTPServer::parseRequest(const std::string &request,
                                     std::string &method, std::string &path,
                                     std::string &body) {
  std::istringstream iss(request);
  iss >> method >> path;

  // Extract body (after empty line)
  size_t bodyStart = request.find("\r\n\r\n");
  if (bodyStart != std::string::npos) {
    body = request.substr(bodyStart + 4);
  }

  return "";
}

std::string HTTPServer::buildResponse(int statusCode, const std::string &body) {
  std::ostringstream response;

  std::string statusText = "OK";
  if (statusCode == 404)
    statusText = "Not Found";
  else if (statusCode == 500)
    statusText = "Internal Server Error";

  response << "HTTP/1.1 " << statusCode << " " << statusText << "\r\n";
  response << "Content-Type: application/json\r\n";
  response << "Content-Length: " << body.length() << "\r\n";
  response << "Access-Control-Allow-Origin: *\r\n";
  response << "Connection: close\r\n";
  response << "\r\n";
  response << body;

  return response.str();
}

std::string HTTPServer::stripQueryString(const std::string &path) {
  const size_t q = path.find('?');
  if (q == std::string::npos) {
    return path;
  }
  return path.substr(0, q);
}

std::vector<std::string> HTTPServer::splitPath(const std::string &path) {
  std::vector<std::string> parts;
  std::string current;
  for (char c : path) {
    if (c == '/') {
      if (!current.empty()) {
        parts.push_back(current);
        current.clear();
      }
    } else {
      current.push_back(c);
    }
  }
  if (!current.empty()) {
    parts.push_back(current);
  }
  return parts;
}

bool HTTPServer::matchRoutePattern(const std::string &pattern,
                                   const std::string &requestPath) {
  if (pattern == requestPath) {
    return true;
  }

  const auto p1 = splitPath(pattern);
  const auto p2 = splitPath(requestPath);
  if (p1.size() != p2.size()) {
    return false;
  }

  for (size_t i = 0; i < p1.size(); ++i) {
    const std::string &a = p1[i];
    const std::string &b = p2[i];

    // Parameter segment: {id}
    if (a.size() >= 2 && a.front() == '{' && a.back() == '}') {
      if (b.empty()) {
        return false;
      }
      continue;
    }

    if (a != b) {
      return false;
    }
  }

  return true;
}

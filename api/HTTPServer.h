#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include <atomic>
#include <functional>
#include <map>
#include <string>
#include <thread>
#include <vector>


// Lightweight HTTP server using cross-platform sockets (Winsock/POSIX)
class HTTPServer {
public:
  using RouteHandler = std::function<std::string(const std::string &method,
                                                 const std::string &path,
                                                 const std::string &body)>;

  HTTPServer(int port);
  ~HTTPServer();

  void registerRoute(const std::string &method, const std::string &path,
                     RouteHandler handler);
  void start();
  void stop();
  bool isRunning() const;

  static std::string stripQueryString(const std::string &path);
  static std::vector<std::string> splitPath(const std::string &path);
  static bool matchRoutePattern(const std::string &pattern,
                               const std::string &requestPath);

private:
  int port;
  std::atomic<bool> running;
  std::thread serverThread;
  std::map<std::string, RouteHandler> routes; // "METHOD:PATH" -> handler

  void serverLoop();
  void handleClient(void *clientSocket);
  std::string parseRequest(const std::string &request, std::string &method,
                           std::string &path, std::string &body);
  std::string buildResponse(int statusCode, const std::string &body);
};

#endif // HTTP_SERVER_H

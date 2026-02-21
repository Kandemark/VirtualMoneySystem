#pragma once
#include <algorithm>
#include <chrono>
#include <condition_variable>
#include <mutex>
#include <vector>


class ConnectionPool {
public:
  struct Connection {
    size_t id;
    bool inUse;
    std::chrono::steady_clock::time_point lastUsed;
    // Add database-specific connection handle here
  };

  explicit ConnectionPool(size_t poolSize = 10);
  ~ConnectionPool();

  Connection *acquire();
  void release(Connection *conn);

  size_t getActiveCount() const;
  size_t getTotalCount() const;
  void shutdown();

private:
  std::vector<Connection> connections;
  size_t maxConnections;
  size_t activeConnections;
  mutable std::mutex poolMutex;
  std::condition_variable cv;
};

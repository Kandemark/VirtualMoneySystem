#include "ConnectionPool.h"

ConnectionPool::ConnectionPool(size_t poolSize)
    : maxConnections(poolSize), activeConnections(0) {
  // Initialize pool with connections
  for (size_t i = 0; i < poolSize; ++i) {
    Connection conn;
    conn.id = i;
    conn.inUse = false;
    conn.lastUsed = std::chrono::steady_clock::now();
    connections.push_back(conn);
  }
}

ConnectionPool::~ConnectionPool() { shutdown(); }

ConnectionPool::Connection *ConnectionPool::acquire() {
  std::unique_lock<std::mutex> lock(poolMutex);

  // Wait for available connection
  cv.wait(lock, [this] {
    return std::any_of(connections.begin(), connections.end(),
                       [](const Connection &c) { return !c.inUse; });
  });

  // Find first available connection
  for (auto &conn : connections) {
    if (!conn.inUse) {
      conn.inUse = true;
      conn.lastUsed = std::chrono::steady_clock::now();
      activeConnections++;
      return &conn;
    }
  }

  return nullptr;
}

void ConnectionPool::release(Connection *conn) {
  if (conn == nullptr) {
    return;
  }

  std::lock_guard<std::mutex> lock(poolMutex);
  conn->inUse = false;
  conn->lastUsed = std::chrono::steady_clock::now();
  activeConnections--;
  cv.notify_one();
}

size_t ConnectionPool::getActiveCount() const {
  std::lock_guard<std::mutex> lock(poolMutex);
  return activeConnections;
}

size_t ConnectionPool::getTotalCount() const { return maxConnections; }

void ConnectionPool::shutdown() {
  std::lock_guard<std::mutex> lock(poolMutex);
  connections.clear();
  activeConnections = 0;
}

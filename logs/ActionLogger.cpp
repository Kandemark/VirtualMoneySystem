
#include "ActionLogger.h"

#include <ctime>
#include <fstream>
#include <mutex>
#include <sstream>
#include <vector>

namespace {
std::mutex g_logsMutex;
std::vector<std::string> g_lines;

std::string nowEpoch() {
  std::ostringstream oss;
  oss << std::time(nullptr);
  return oss.str();
}
} // namespace

void ActionLoggerLogs::logAction(const std::string &action,
                                 const std::string &userId) {
  std::ostringstream oss;
  oss << nowEpoch() << " userId=" << userId << " action=" << action;
  std::lock_guard<std::mutex> lock(g_logsMutex);
  g_lines.push_back(oss.str());
}

void ActionLoggerLogs::logToFile(const std::string &filename) {
  std::lock_guard<std::mutex> lock(g_logsMutex);
  std::ofstream out(filename.empty() ? "logs/action.log" : filename,
                    std::ios::app);
  if (!out.is_open()) {
    return;
  }
  for (const auto &line : g_lines) {
    out << line << "\n";
  }
  g_lines.clear();
}

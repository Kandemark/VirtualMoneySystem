
#include "EventLogger.h"

#include <ctime>
#include <fstream>
#include <mutex>
#include <sstream>
#include <unordered_map>
#include <vector>

namespace {
std::mutex g_eventMutex;
std::unordered_map<std::string, std::vector<std::string>> g_byType;

std::string nowEpoch() {
  std::ostringstream oss;
  oss << std::time(nullptr);
  return oss.str();
}

void appendLine(const std::string &file, const std::string &line) {
  std::ofstream out(file, std::ios::app);
  if (!out.is_open()) {
    return;
  }
  out << line << "\n";
}
} // namespace

void EventLogger::logEvent(const std::string &eventType,
                           const std::string &eventData) {
  std::ostringstream oss;
  oss << nowEpoch() << " type=" << eventType << " data=" << eventData;
  const std::string line = oss.str();

  {
    std::lock_guard<std::mutex> lock(g_eventMutex);
    g_byType[eventType].push_back(line);
  }
  appendLine("logs/history_events.log", line);
}

void EventLogger::logError(const std::string &error, const std::string &context) {
  std::ostringstream oss;
  oss << nowEpoch() << " error=" << error << " context=" << context;
  const std::string line = oss.str();

  {
    std::lock_guard<std::mutex> lock(g_eventMutex);
    g_byType["error"].push_back(line);
  }
  appendLine("logs/history_errors.log", line);
}

void EventLogger::logWarning(const std::string &warning) {
  logEvent("warning", warning);
}

std::string EventLogger::getEventLog(const std::string &eventType) {
  std::lock_guard<std::mutex> lock(g_eventMutex);
  auto it = g_byType.find(eventType);
  if (it == g_byType.end()) {
    return "";
  }

  std::ostringstream oss;
  for (const auto &line : it->second) {
    oss << line << "\n";
  }
  return oss.str();
}

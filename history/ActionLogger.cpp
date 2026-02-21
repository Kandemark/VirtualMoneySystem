
#include "ActionLogger.h"

#include <ctime>
#include <fstream>
#include <mutex>
#include <sstream>
#include <unordered_map>
#include <vector>

namespace {
std::mutex g_actionMutex;
std::unordered_map<std::string, std::vector<std::string>> g_byActor;

std::string nowEpoch() {
  std::ostringstream oss;
  oss << std::time(nullptr);
  return oss.str();
}

void appendLine(const std::string &line) {
  std::ofstream out("logs/history_actions.log", std::ios::app);
  if (!out.is_open()) {
    return;
  }
  out << line << "\n";
}
} // namespace

void ActionLogger::logAction(const std::string &actor, const std::string &action,
                             const std::string &target) {
  std::ostringstream oss;
  oss << nowEpoch() << " actor=" << actor << " action=" << action
      << " target=" << target;
  const std::string line = oss.str();

  {
    std::lock_guard<std::mutex> lock(g_actionMutex);
    g_byActor[actor].push_back(line);
  }
  appendLine(line);
}

void ActionLogger::logAPICall(const std::string &endpoint, const std::string &method,
                              const std::string &userId) {
  logAction(userId, std::string("api:") + method + " " + endpoint, endpoint);
}

std::string ActionLogger::getActionLog(const std::string &actor) {
  std::lock_guard<std::mutex> lock(g_actionMutex);
  auto it = g_byActor.find(actor);
  if (it == g_byActor.end()) {
    return "";
  }

  std::ostringstream oss;
  for (const auto &line : it->second) {
    oss << line << "\n";
  }
  return oss.str();
}

#include "OfflineCommandQueue.h"

#include <queue>

namespace { std::queue<std::string> g_queue; }

void OfflineCommandQueue::queueCommand(const std::string& command, const std::string& userId) { g_queue.push(userId + ":" + command); }
void OfflineCommandQueue::processQueue() { while (!g_queue.empty()) g_queue.pop(); }
std::vector<std::string> OfflineCommandQueue::getPendingCommands() {
    std::vector<std::string> out; std::queue<std::string> c = g_queue;
    while (!c.empty()) { out.push_back(c.front()); c.pop(); }
    return out;
}
void OfflineCommandQueue::clearQueue() { while (!g_queue.empty()) g_queue.pop(); }

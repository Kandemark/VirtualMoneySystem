#include "AdminPortal.h"

AdminPortal::AdminPortal() {}

std::vector<std::string> AdminPortal::getSystemStats() const {
    return {"Users: 1000", "Transactions: 50000", "Uptime: 99.9%"};
}

bool AdminPortal::executeCommand(const std::string& command) {
    return true;
}

std::string AdminPortal::getSystemHealth() const {
    return "HEALTHY";
}

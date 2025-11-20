#ifndef ADMIN_PORTAL_H
#define ADMIN_PORTAL_H
#include <string>
#include <vector>

class AdminPortal {
public:
    AdminPortal();
    std::vector<std::string> getSystemStats() const;
    bool executeCommand(const std::string& command);
    std::string getSystemHealth() const;
};

#endif

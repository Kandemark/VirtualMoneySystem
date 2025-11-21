/**
 * @file AutoRepairDaemon.h
 * @brief Automatic system repair daemon
 */

#ifndef AUTO_REPAIR_DAEMON_H
#define AUTO_REPAIR_DAEMON_H

#include <string>

class AutoRepairDaemon {
public:
    void start();
    void stop();
    void detectIssues();
    void repairIssue(const std::string& issueId);
    bool isRunning();
};

#endif

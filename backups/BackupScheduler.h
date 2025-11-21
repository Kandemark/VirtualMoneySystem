/**
 * @file BackupScheduler.h
 * @brief Automated backup scheduling
 */

#ifndef BACKUP_SCHEDULER_H
#define BACKUP_SCHEDULER_H

#include <string>

class BackupScheduler {
public:
    void scheduleBackup(const std::string& cronExpression);
    void runBackup();
    void setBackupLocation(const std::string& path);
    std::string getLastBackupTime();
};

#endif

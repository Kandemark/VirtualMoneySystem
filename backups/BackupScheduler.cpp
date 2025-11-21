/**
 * @file BackupScheduler.cpp
 */

#include "BackupScheduler.h"
#include <iostream>

namespace VirtualMoney {

BackupScheduler::BackupScheduler() {}

void BackupScheduler::scheduleBackup(const std::string& schedule) {
    std::cout << "Backup scheduled: " << schedule << std::endl;
}

bool BackupScheduler::createBackup() {
    std::string backupId = "backup_" + std::to_string(std::time(nullptr));
    backups.push_back(backupId);
    std::cout << "Backup created: " << backupId << std::endl;
    return true;
}

std::vector<std::string> BackupScheduler::listBackups() const {
    return backups;
}

bool BackupScheduler::deleteOldBackups(int daysToKeep) {
    std::cout << "Deleting backups older than " << daysToKeep << " days" << std::endl;
    return true;
}

} // namespace VirtualMoney

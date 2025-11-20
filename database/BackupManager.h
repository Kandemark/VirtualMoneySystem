#ifndef BACKUP_MANAGER_H
#define BACKUP_MANAGER_H

#include <string>

class BackupManager {
public:
    BackupManager(const std::string& dbPath, const std::string& backupDir);

    bool createBackup();

private:
    std::string dbPath;
    std::string backupDir;
};

#endif // BACKUP_MANAGER_H

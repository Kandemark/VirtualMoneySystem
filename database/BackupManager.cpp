#include "BackupManager.h"
#include <filesystem>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <iostream>

namespace fs = std::filesystem;

BackupManager::BackupManager(const std::string& dbPath, const std::string& backupDir)
    : dbPath(dbPath), backupDir(backupDir) {}

bool BackupManager::createBackup() {
    try {
        if (!fs::exists(backupDir)) {
            fs::create_directories(backupDir);
        }

        auto now = std::chrono::system_clock::now();
        std::time_t time = std::chrono::system_clock::to_time_t(now);
        std::stringstream ss;
        ss << std::put_time(std::localtime(&time), "%Y%m%d_%H%M%S");
        
        std::string filename = "backup_" + ss.str() + ".db";
        fs::path source(dbPath);
        fs::path destination = fs::path(backupDir) / filename;

        fs::copy_file(source, destination, fs::copy_options::overwrite_existing);
        std::cout << "Backup created successfully: " << destination << std::endl;
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Backup failed: " << e.what() << std::endl;
        return false;
    }
}

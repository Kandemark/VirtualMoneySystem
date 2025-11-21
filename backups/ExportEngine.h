/**
 * @file ExportEngine.h
 * @brief Data export engine for backups
 */

#ifndef EXPORT_ENGINE_BACKUPS_H
#define EXPORT_ENGINE_BACKUPS_H

#include <string>

class ExportEngine {
public:
    void exportData(const std::string& dataType, const std::string& outputPath);
    void setFormat(const std::string& format);
    bool exportComplete();
};

#endif

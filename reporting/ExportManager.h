/**
 * @file ExportManager.h
 * @brief Export data in various formats
 */

#ifndef EXPORT_MANAGER_H
#define EXPORT_MANAGER_H

#include <string>

class ExportManager {
public:
    std::string exportToCSV(const std::string& dataId);
    std::string exportToPDF(const std::string& dataId);
    std::string exportToExcel(const std::string& dataId);
    std::string exportToJSON(const std::string& dataId);
};

#endif

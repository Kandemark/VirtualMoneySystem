#include "ExportManager.h"

std::string ExportManager::exportToCSV(const std::string& dataId) {
    return "export_" + dataId + ".csv";
}

std::string ExportManager::exportToPDF(const std::string& dataId) {
    return "export_" + dataId + ".pdf";
}

std::string ExportManager::exportToExcel(const std::string& dataId) {
    return "export_" + dataId + ".xlsx";
}

std::string ExportManager::exportToJSON(const std::string& dataId) {
    return "export_" + dataId + ".json";
}

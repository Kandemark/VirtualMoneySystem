/**
 * @file DataExportManager.h
 * @brief Centralized data export management
 */

#ifndef DATA_EXPORT_MANAGER_H
#define DATA_EXPORT_MANAGER_H

#include <string>
#include <vector>

/**
 * @brief Manages data exports
 */
class DataExportManager {
public:
    /**
     * @brief Request data export
     * @param userId User identifier
     * @param dataType Type of data to export
     * @param format Export format (CSV, PDF, JSON)
     * @return Export job ID
     */
    std::string requestExport(const std::string& userId, const std::string& dataType, const std::string& format);
    
    /**
     * @brief Get export status
     * @param jobId Export job ID
     * @return Status string
     */
    std::string getExportStatus(const std::string& jobId);
    
    /**
     * @brief Download export
     * @param jobId Export job ID
     * @return File path
     */
    std::string downloadExport(const std::string& jobId);
    
    /**
     * @brief List user exports
     * @param userId User identifier
     * @return Vector of export job IDs
     */
    std::vector<std::string> listExports(const std::string& userId);
};

#endif

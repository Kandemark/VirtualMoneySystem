/**
 * @file ExportEngine.h
 * @brief Core export engine
 */

#ifndef EXPORT_ENGINE_H
#define EXPORT_ENGINE_H

#include <string>
#include <vector>
#include <map>

/**
 * @brief Core data export engine
 */
class ExportEngine {
public:
    /**
     * @brief Export data
     * @param data Data to export
     * @param format Target format
     * @param options Export options
     * @return Exported data string
     */
    std::string exportData(const std::string& data, const std::string& format, 
                          const std::map<std::string, std::string>& options = {});
    
    /**
     * @brief Register export format
     * @param format Format name
     * @param handler Format handler
     */
    void registerFormat(const std::string& format, const std::string& handler);
    
    /**
     * @brief Get supported formats
     * @return Vector of format names
     */
    std::vector<std::string> getSupportedFormats();
};

#endif

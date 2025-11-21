/**
 * @file CSVExporter.h
 * @brief Export data to CSV format
 */

#ifndef CSV_EXPORTER_H
#define CSV_EXPORTER_H

#include <string>
#include <vector>

/**
 * @brief Exports data to CSV files
 */
class CSVExporter {
public:
    /**
     * @brief Export to CSV
     * @param data Data to export (rows of columns)
     * @param headers Column headers
     * @param filename Output filename
     * @return true if successful
     */
    bool exportToCSV(const std::vector<std::vector<std::string>>& data, 
                     const std::vector<std::string>& headers,
                     const std::string& filename);
    
    /**
     * @brief Set delimiter
     * @param delimiter CSV delimiter character
     */
    void setDelimiter(char delimiter);
    
    /**
     * @brief Enable/disable quotes
     * @param enabled true to quote all fields
     */
    void setQuoteAll(bool enabled);

private:
    char delimiter = ',';
    bool quoteAll = false;
};

#endif

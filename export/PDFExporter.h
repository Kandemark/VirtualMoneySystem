/**
 * @file PDFExporter.h
 * @brief Export data to PDF format
 */

#ifndef PDF_EXPORTER_H
#define PDF_EXPORTER_H

#include <string>
#include <vector>

/**
 * @brief Exports data to PDF files
 */
class PDFExporter {
public:
    /**
     * @brief Export to PDF
     * @param content Content to export
     * @param filename Output filename
     * @return true if successful
     */
    bool exportToPDF(const std::string& content, const std::string& filename);
    
    /**
     * @brief Add table to PDF
     * @param data Table data
     * @param headers Table headers
     */
    void addTable(const std::vector<std::vector<std::string>>& data,
                  const std::vector<std::string>& headers);
    
    /**
     * @brief Set page size
     * @param size Page size (A4, Letter, etc.)
     */
    void setPageSize(const std::string& size);

private:
    std::string pageSize = "A4";
};

#endif

/**
 * @file PDFGenerator.h
 * @brief Advanced PDF generation
 */

#ifndef PDF_GENERATOR_H
#define PDF_GENERATOR_H

#include <string>

/**
 * @brief Advanced PDF document generation
 */
class PDFGenerator {
public:
    /**
     * @brief Create new PDF document
     * @param title Document title
     * @return Document ID
     */
    std::string createDocument(const std::string& title);
    
    /**
     * @brief Add page
     * @param docId Document ID
     */
    void addPage(const std::string& docId);
    
    /**
     * @brief Add text
     * @param docId Document ID
     * @param text Text content
     * @param x X position
     * @param y Y position
     */
    void addText(const std::string& docId, const std::string& text, int x, int y);
    
    /**
     * @brief Save document
     * @param docId Document ID
     * @param filename Output filename
     * @return true if successful
     */
    bool saveDocument(const std::string& docId, const std::string& filename);
};

#endif

/**
 * @file DocumentScanner.h
 * @brief Document scanning and verification
 */

#ifndef DOCUMENT_SCANNER_H
#define DOCUMENT_SCANNER_H

#include <string>

class DocumentScanner {
public:
    bool scanDocument(const std::string& documentPath);
    std::string extractText(const std::string& documentPath);
    bool verifyDocument(const std::string& documentId);
    std::string getDocumentType(const std::string& documentPath);
};

#endif

#include "DocumentScanner.h"

#include <fstream>

bool DocumentScanner::scanDocument(const std::string& documentPath) { std::ifstream in(documentPath); return in.good(); }
std::string DocumentScanner::extractText(const std::string& documentPath) { return scanDocument(documentPath) ? "DOCUMENT_TEXT" : ""; }
bool DocumentScanner::verifyDocument(const std::string& documentId) { return !documentId.empty(); }
std::string DocumentScanner::getDocumentType(const std::string& documentPath) { auto p=documentPath.rfind('.'); return p==std::string::npos?"unknown":documentPath.substr(p+1); }

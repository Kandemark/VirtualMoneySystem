#include "PDFExporter.h"

#include <fstream>

bool PDFExporter::exportToPDF(const std::string& content, const std::string& filename) {
    std::ofstream out(filename);
    if (!out) return false;
    out << "PDF(" << pageSize << ")
" << content << '
';
    return true;
}
void PDFExporter::addTable(const std::vector<std::vector<std::string>>&, const std::vector<std::string>&) {}
void PDFExporter::setPageSize(const std::string& size) { pageSize = size; }

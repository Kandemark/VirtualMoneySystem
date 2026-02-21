#include "PDFGenerator.h"

#include <fstream>
#include <unordered_map>
#include <vector>

namespace {
std::unordered_map<std::string, std::vector<std::string>> g_docs;
}

std::string PDFGenerator::createDocument(const std::string& title) {
    const std::string id = "pdf_" + std::to_string(std::hash<std::string>{}(title));
    g_docs[id].push_back("TITLE:" + title);
    return id;
}

void PDFGenerator::addPage(const std::string& docId) { g_docs[docId].push_back("---PAGE---"); }

void PDFGenerator::addText(const std::string& docId, const std::string& text, int, int) {
    g_docs[docId].push_back(text);
}

bool PDFGenerator::saveDocument(const std::string& docId, const std::string& filename) {
    std::ofstream out(filename);
    if (!out) {
        return false;
    }

    for (const auto& line : g_docs[docId]) {
        out << line << '\n';
    }

    return true;
}

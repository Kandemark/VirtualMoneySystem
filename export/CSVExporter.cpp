#include "CSVExporter.h"

#include <fstream>

bool CSVExporter::exportToCSV(const std::vector<std::vector<std::string>>& data,
                              const std::vector<std::string>& headers,
                              const std::string& filename) {
    std::ofstream out(filename);
    if (!out) {
        return false;
    }

    auto writeCell = [&](const std::string& v) {
        if (quoteAll) {
            out << '"' << v << '"';
        } else {
            out << v;
        }
    };

    for (size_t i = 0; i < headers.size(); ++i) {
        writeCell(headers[i]);
        if (i + 1 < headers.size()) {
            out << delimiter;
        }
    }
    out << '\n';

    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            writeCell(row[i]);
            if (i + 1 < row.size()) {
                out << delimiter;
            }
        }
        out << '\n';
    }

    return true;
}

void CSVExporter::setDelimiter(char d) { delimiter = d; }

void CSVExporter::setQuoteAll(bool enabled) { quoteAll = enabled; }

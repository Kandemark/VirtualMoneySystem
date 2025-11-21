/**
 * @file ExportEngine.cpp
 */

#include "ExportEngine.h"
#include <iostream>
#include <fstream>

namespace VirtualMoney {

ExportEngine::ExportEngine() {}

bool ExportEngine::exportToCSV(const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << "id,timestamp,amount,status\n";
        file << "TX_1,2025-11-21,100.00,completed\n";
        file.close();
        std::cout << "Exported to CSV: " << filename << std::endl;
        return true;
    }
    return false;
}

bool ExportEngine::exportToJSON(const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << "[{\"id\":\"TX_1\",\"amount\":100.00}]\n";
        file.close();
        std::cout << "Exported to JSON: " << filename << std::endl;
        return true;
    }
    return false;
}

bool ExportEngine::exportToXML(const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << "<?xml version=\"1.0\"?>\n<transactions></transactions>\n";
        file.close();
        std::cout << "Exported to XML: " << filename << std::endl;
        return true;
    }
    return false;
}

} // namespace VirtualMoney

/**
 * @file ImmutableLogger.cpp
 */

#include "ImmutableLogger.h"
#include <iostream>
#include <fstream>

namespace VirtualMoney {

ImmutableLogger::ImmutableLogger(const std::string& logFile) : logFile(logFile) {}

void ImmutableLogger::log(const std::string& event, const std::string& data) {
    LogEntry entry;
    entry.timestamp = std::time(nullptr);
    entry.event = event;
    entry.data = data;
    entry.hash = calculateHash(entry);
    
    entries.push_back(entry);
    
    std::cout << "Immutable log: " << event << std::endl;
    
    writeToFile(entry);
}

std::vector<LogEntry> ImmutableLogger::getEntries() const {
    return entries;
}

bool ImmutableLogger::verify() const {
    for (const auto& entry : entries) {
        if (calculateHash(entry) != entry.hash) {
            return false;
        }
    }
    return true;
}

std::string ImmutableLogger::calculateHash(const LogEntry& entry) const {
    // Simplified hash (in production, use SHA-256)
    return std::to_string(entry.timestamp) + "_" + entry.event;
}

void ImmutableLogger::writeToFile(const LogEntry& entry) {
    std::ofstream file(logFile, std::ios::app);
    if (file.is_open()) {
        file << entry.timestamp << "," << entry.event << "," << entry.data << "," << entry.hash << std::endl;
        file.close();
    }
}

} // namespace VirtualMoney

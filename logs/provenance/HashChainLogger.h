/**
 * @file HashChainLogger.h
 * @brief Hash chain provenance logging
 */

#ifndef HASH_CHAIN_LOGGER_H
#define HASH_CHAIN_LOGGER_H

#include <string>

class HashChainLogger {
public:
    void logEntry(const std::string& data);
    std::string getChainHash();
    bool verifyChain();
    std::string getEntry(int index);
};

#endif

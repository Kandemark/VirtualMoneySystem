/**
 * @file generate_keys.h
 * @brief Cryptographic key generation utility
 */

#ifndef GENERATE_KEYS_H
#define GENERATE_KEYS_H

#include <string>

void generateRSAKeys(const std::string& outputPath);
void generateAESKey(const std::string& outputPath);
void generateKeyPair(const std::string& algorithm, const std::string& outputPath);

#endif

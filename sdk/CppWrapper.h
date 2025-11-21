/**
 * @file CppWrapper.h
 * @brief C++ SDK wrapper
 */

#ifndef CPP_WRAPPER_H
#define CPP_WRAPPER_H

#include <string>

class CppWrapper {
public:
    void initialize(const std::string& apiKey);
    std::string createWallet(const std::string& userId);
    std::string makeTransaction(const std::string& fromWallet, const std::string& toWallet, double amount);
};

#endif

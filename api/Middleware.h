/**
 * @file Middleware.h
 * @brief API middleware
 */

#ifndef MIDDLEWARE_H
#define MIDDLEWARE_H

#include <string>
#include <functional>

class Middleware {
public:
    void use(std::function<void(const std::string&)> handler);
    void authenticate(const std::string& token);
    void logRequest(const std::string& request);
    void validateInput(const std::string& input);
};

#endif

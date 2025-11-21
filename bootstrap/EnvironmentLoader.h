/**
 * @file EnvironmentLoader.h
 * @brief Environment configuration loader
 */

#ifndef ENVIRONMENT_LOADER_H
#define ENVIRONMENT_LOADER_H

#include <string>
#include <map>

class EnvironmentLoader {
public:
    void loadFromFile(const std::string& filename);
    std::string get(const std::string& key);
    void set(const std::string& key, const std::string& value);
    std::map<std::string, std::string> getAll();
};

#endif

/**
 * @file EnvironmentLoader.cpp
 */

#include "EnvironmentLoader.h"
#include <iostream>
#include <fstream>

namespace VirtualMoney {

EnvironmentLoader::EnvironmentLoader() {}

bool EnvironmentLoader::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            size_t pos = line.find('=');
            if (pos != std::string::npos) {
                std::string key = line.substr(0, pos);
                std::string value = line.substr(pos + 1);
                env[key] = value;
            }
        }
        file.close();
        std::cout << "Environment loaded from: " << filename << std::endl;
        return true;
    }
    return false;
}

std::string EnvironmentLoader::get(const std::string& key) const {
    auto it = env.find(key);
    if (it != env.end()) {
        return it->second;
    }
    return "";
}

void EnvironmentLoader::set(const std::string& key, const std::string& value) {
    env[key] = value;
}

} // namespace VirtualMoney

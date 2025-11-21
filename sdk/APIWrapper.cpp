#include "APIWrapper.h"
#include <iostream>

std::string APIWrapper::get(const std::string& endpoint, const std::map<std::string, std::string>& params) {
    std::cout << "[API] GET " << endpoint << std::endl;
    return "{\"status\": \"success\"}";
}

std::string APIWrapper::post(const std::string& endpoint, const std::string& data) {
    std::cout << "[API] POST " << endpoint << " - " << data << std::endl;
    return "{\"status\": \"success\"}";
}

void APIWrapper::setAuthToken(const std::string& token) {
    authToken = token;
}

#include "RuleDSLParser.h"

#include <algorithm>
#include <sstream>

std::map<std::string, std::string> RuleDSLParser::parse(const std::string& expression) {
    std::map<std::string, std::string> parsed;
    std::stringstream ss(expression);
    std::string token;
    while (std::getline(ss, token, ';')) {
        auto pos = token.find('=');
        if (pos == std::string::npos) continue;
        auto key = token.substr(0, pos);
        auto value = token.substr(pos + 1);
        key.erase(std::remove_if(key.begin(), key.end(), ::isspace), key.end());
        value.erase(0, value.find_first_not_of(" \t"));
        if (!key.empty()) parsed[key] = value;
    }
    return parsed;
}

bool RuleDSLParser::validate(const std::string& expression) {
    return !expression.empty() && expression.find('=') != std::string::npos;
}

std::string RuleDSLParser::compile(const std::string& expression) {
    if (!validate(expression)) return "";
    return "rule_" + std::to_string(std::hash<std::string>{}(expression));
}

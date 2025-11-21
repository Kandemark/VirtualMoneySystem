/**
 * @file PersonalRules.h
 * @brief Personal compliance rules
 */

#ifndef PERSONAL_RULES_H
#define PERSONAL_RULES_H

#include <string>

class PersonalRules {
public:
    void setUserRule(const std::string& userId, const std::string& rule, const std::string& value);
    std::string getUserRule(const std::string& userId, const std::string& rule);
    bool checkUserCompliance(const std::string& userId);
};

#endif

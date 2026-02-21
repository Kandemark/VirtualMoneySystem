#include "PersonalRules.h"

#include <unordered_map>

namespace { std::unordered_map<std::string, std::unordered_map<std::string, std::string>> g_rules; }

void PersonalRules::setUserRule(const std::string& userId, const std::string& rule, const std::string& value) { g_rules[userId][rule] = value; }
std::string PersonalRules::getUserRule(const std::string& userId, const std::string& rule) { return g_rules[userId][rule]; }
bool PersonalRules::checkUserCompliance(const std::string& userId) { return !g_rules[userId].empty(); }

/**
 * @file RuleDSLParser.h
 * @brief Domain-specific language parser for rules
 */

#ifndef RULE_DSL_PARSER_H
#define RULE_DSL_PARSER_H

#include <string>
#include <map>

/**
 * @brief Parses rule DSL expressions
 */
class RuleDSLParser {
public:
    /**
     * @brief Parse DSL expression
     * @param expression DSL expression string
     * @return Parsed rule structure
     */
    std::map<std::string, std::string> parse(const std::string& expression);
    
    /**
     * @brief Validate DSL syntax
     * @param expression DSL expression
     * @return true if valid
     */
    bool validate(const std::string& expression);
    
    /**
     * @brief Compile DSL to executable rule
     * @param expression DSL expression
     * @return Compiled rule ID
     */
    std::string compile(const std::string& expression);
};

#endif

/**
 * @file SandboxCLI.h
 * @brief Command-line interface for sandbox testing
 */

#ifndef SANDBOX_CLI_H
#define SANDBOX_CLI_H

#include <string>

class SandboxCLI {
public:
    void start();
    void executeCommand(const std::string& command);
    void printHelp();
    void loadScript(const std::string& scriptFile);
};

#endif

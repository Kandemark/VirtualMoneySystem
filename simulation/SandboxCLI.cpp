/**
 * @file SandboxCLI.cpp
 */

#include "SandboxCLI.h"
#include <iostream>
#include <sstream>

SandboxCLI::SandboxCLI() {}

void SandboxCLI::run() {
    std::cout << "VirtualMoney Sandbox CLI" << std::endl;
    std::cout << "Type 'help' for commands" << std::endl;
    
    std::string input;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);
        
        if (input == "exit") break;
        
        processCommand(input);
    }
}

void SandboxCLI::processCommand(const std::string& command) {
    std::istringstream iss(command);
    std::string cmd;
    iss >> cmd;
    
    if (cmd == "help") {
        showHelp();
    } else if (cmd == "create") {
        std::string type;
        iss >> type;
        if (type == "wallet") {
            std::cout << "Wallet created: WALLET_123" << std::endl;
        }
    } else if (cmd == "balance") {
        std::string walletId;
        iss >> walletId;
        std::cout << "Balance: $1000.00" << std::endl;
    } else {
        std::cout << "Unknown command. Type 'help' for available commands." << std::endl;
    }
}

void SandboxCLI::showHelp() {
    std::cout << "Available commands:" << std::endl;
    std::cout << "  create wallet - Create a new wallet" << std::endl;
    std::cout << "  balance <id> - Check wallet balance" << std::endl;
    std::cout << "  transfer <from> <to> <amount> - Transfer funds" << std::endl;
    std::cout << "  exit - Exit sandbox" << std::endl;
}

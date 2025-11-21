/**
 * @file Server.cpp
 */

#include "Server.h"
#include <iostream>

namespace VirtualMoney {

Server::Server(int port) : port(port), running(false) {}

void Server::start() {
    running = true;
    std::cout << "Server started on port " << port << std::endl;
}

void Server::stop() {
    running = false;
    std::cout << "Server stopped" << std::endl;
}

bool Server::isRunning() const {
    return running;
}

} // namespace VirtualMoney

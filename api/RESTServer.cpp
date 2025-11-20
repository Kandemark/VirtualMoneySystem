#include "RESTServer.h"
#include <iostream>

RESTServer::RESTServer(WalletEndpoints& walletEndpoints)
    : walletEndpoints(walletEndpoints) {
    
    // Register all routes
    this->walletEndpoints.registerRoutes(app);
}

void RESTServer::run(int port) {
    std::cout << "Starting REST Server on port " << port << std::endl;
    app.port(port).multithreaded().run();
}

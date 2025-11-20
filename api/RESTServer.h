#ifndef REST_SERVER_H
#define REST_SERVER_H

#include "../vendor/crow/crow.h"
#include "WalletEndpoints.h"

class RESTServer {
public:
    RESTServer(WalletEndpoints& walletEndpoints);
    void run(int port);

private:
    crow::SimpleApp app;
    WalletEndpoints& walletEndpoints;
};

#endif // REST_SERVER_H

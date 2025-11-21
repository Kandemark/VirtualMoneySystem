/**
 * @file Server.h
 * @brief HTTP server
 */

#ifndef SERVER_H
#define SERVER_H

#include <string>

class Server {
public:
    void start(int port);
    void stop();
    void setMaxConnections(int max);
    bool isRunning();
};

#endif

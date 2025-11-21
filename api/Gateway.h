/**
 * @file Gateway.h
 * @brief API Gateway
 */

#ifndef GATEWAY_H
#define GATEWAY_H

#include <string>

class Gateway {
public:
    void start(int port);
    void stop();
    void registerRoute(const std::string& path, const std::string& handler);
    void setRateLimit(int requestsPerMinute);
};

#endif

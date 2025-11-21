/**
 * @file WebSocketServer.h
 * @brief Real-time WebSocket server for live updates
 */

#ifndef WEBSOCKET_SERVER_H
#define WEBSOCKET_SERVER_H

#include <string>
#include <map>
#include <vector>
#include <functional>

namespace VirtualMoney {

struct WebSocketClient {
    std::string clientId;
    std::string userId;
    bool authenticated;
    std::vector<std::string> subscriptions;
};

class WebSocketServer {
public:
    WebSocketServer(int port);
    
    /**
     * @brief Start WebSocket server
     */
    void start();
    
    /**
     * @brief Stop WebSocket server
     */
    void stop();
    
    /**
     * @brief Broadcast message to all clients
     */
    void broadcast(const std::string& message);
    
    /**
     * @brief Send message to specific client
     */
    void sendToClient(const std::string& clientId, const std::string& message);
    
    /**
     * @brief Send to all subscribers of a channel
     */
    void sendToChannel(const std::string& channel, const std::string& message);
    
    /**
     * @brief Subscribe client to channel
     */
    bool subscribe(const std::string& clientId, const std::string& channel);
    
    /**
     * @brief Unsubscribe client from channel
     */
    bool unsubscribe(const std::string& clientId, const std::string& channel);
    
    /**
     * @brief Get connected clients count
     */
    int getClientCount() const;
    
    /**
     * @brief Notify balance update
     */
    void notifyBalanceUpdate(const std::string& userId, double newBalance);
    
    /**
     * @brief Notify transaction
     */
    void notifyTransaction(const std::string& userId, const std::string& txId);
    
private:
    int port;
    bool running;
    std::map<std::string, WebSocketClient> clients;
    std::map<std::string, std::vector<std::string>> channels; // channel -> clientIds
    
    void handleConnection(const std::string& clientId);
    void handleDisconnection(const std::string& clientId);
    void handleMessage(const std::string& clientId, const std::string& message);
};

} // namespace VirtualMoney

#endif

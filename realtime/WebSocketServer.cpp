/**
 * @file WebSocketServer.cpp
 */

#include "WebSocketServer.h"
#include <iostream>
#include <algorithm>

namespace VirtualMoney {

WebSocketServer::WebSocketServer(int port) : port(port), running(false) {}

void WebSocketServer::start() {
    running = true;
    std::cout << "WebSocket server started on port " << port << std::endl;
}

void WebSocketServer::stop() {
    running = false;
    std::cout << "WebSocket server stopped" << std::endl;
}

void WebSocketServer::broadcast(const std::string& message) {
    std::cout << "Broadcasting to " << clients.size() << " clients: " << message << std::endl;
    
    for (const auto& [clientId, client] : clients) {
        sendToClient(clientId, message);
    }
}

void WebSocketServer::sendToClient(const std::string& clientId, const std::string& message) {
    auto it = clients.find(clientId);
    if (it != clients.end()) {
        std::cout << "Sending to client " << clientId << ": " << message << std::endl;
        // In production: actual WebSocket send
    }
}

void WebSocketServer::sendToChannel(const std::string& channel, const std::string& message) {
    auto it = channels.find(channel);
    if (it != channels.end()) {
        std::cout << "Sending to channel " << channel << " (" << it->second.size() << " subscribers)" << std::endl;
        
        for (const auto& clientId : it->second) {
            sendToClient(clientId, message);
        }
    }
}

bool WebSocketServer::subscribe(const std::string& clientId, const std::string& channel) {
    auto clientIt = clients.find(clientId);
    if (clientIt == clients.end()) {
        return false;
    }
    
    // Add to client's subscriptions
    clientIt->second.subscriptions.push_back(channel);
    
    // Add to channel's subscribers
    channels[channel].push_back(clientId);
    
    std::cout << "Client " << clientId << " subscribed to " << channel << std::endl;
    
    return true;
}

bool WebSocketServer::unsubscribe(const std::string& clientId, const std::string& channel) {
    auto clientIt = clients.find(clientId);
    if (clientIt == clients.end()) {
        return false;
    }
    
    // Remove from client's subscriptions
    auto& subs = clientIt->second.subscriptions;
    subs.erase(std::remove(subs.begin(), subs.end(), channel), subs.end());
    
    // Remove from channel's subscribers
    auto channelIt = channels.find(channel);
    if (channelIt != channels.end()) {
        auto& subscribers = channelIt->second;
        subscribers.erase(std::remove(subscribers.begin(), subscribers.end(), clientId), subscribers.end());
    }
    
    std::cout << "Client " << clientId << " unsubscribed from " << channel << std::endl;
    
    return true;
}

int WebSocketServer::getClientCount() const {
    return clients.size();
}

void WebSocketServer::notifyBalanceUpdate(const std::string& userId, double newBalance) {
    std::string message = "{\"type\":\"balance_update\",\"userId\":\"" + userId + 
                         "\",\"balance\":" + std::to_string(newBalance) + "}";
    
    sendToChannel("balance_" + userId, message);
}

void WebSocketServer::notifyTransaction(const std::string& userId, const std::string& txId) {
    std::string message = "{\"type\":\"transaction\",\"userId\":\"" + userId + 
                         "\",\"txId\":\"" + txId + "\"}";
    
    sendToChannel("transactions_" + userId, message);
}

void WebSocketServer::handleConnection(const std::string& clientId) {
    WebSocketClient client;
    client.clientId = clientId;
    client.authenticated = false;
    
    clients[clientId] = client;
    
    std::cout << "Client connected: " << clientId << std::endl;
}

void WebSocketServer::handleDisconnection(const std::string& clientId) {
    auto it = clients.find(clientId);
    if (it != clients.end()) {
        // Unsubscribe from all channels
        for (const auto& channel : it->second.subscriptions) {
            unsubscribe(clientId, channel);
        }
        
        clients.erase(it);
        std::cout << "Client disconnected: " << clientId << std::endl;
    }
}

void WebSocketServer::handleMessage(const std::string& clientId, const std::string& message) {
    std::cout << "Message from " << clientId << ": " << message << std::endl;
    // In production: parse and handle message
}

} // namespace VirtualMoney

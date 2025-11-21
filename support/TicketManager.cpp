/**
 * @file TicketManager.cpp
 */

#include "TicketManager.h"
#include <iostream>
#include <random>

TicketManager::TicketManager() {}

std::string TicketManager::createTicket(const std::string& userId, const std::string& subject, const std::string& description) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(100000, 999999);
    
    Ticket ticket;
    ticket.ticketId = "TICKET_" + std::to_string(dis(gen));
    ticket.userId = userId;
    ticket.subject = subject;
    ticket.description = description;
    ticket.status = "open";
    ticket.priority = "normal";
    ticket.createdAt = std::time(nullptr);
    
    tickets[ticket.ticketId] = ticket;
    
    std::cout << "Support ticket created: " << ticket.ticketId << std::endl;
    
    return ticket.ticketId;
}

bool TicketManager::updateStatus(const std::string& ticketId, const std::string& status) {
    auto it = tickets.find(ticketId);
    if (it != tickets.end()) {
        it->second.status = status;
        std::cout << "Ticket " << ticketId << " status updated to: " << status << std::endl;
        return true;
    }
    return false;
}

Ticket TicketManager::getTicket(const std::string& ticketId) const {
    auto it = tickets.find(ticketId);
    if (it != tickets.end()) {
        return it->second;
    }
    return Ticket();
}

std::vector<Ticket> TicketManager::getUserTickets(const std::string& userId) const {
    std::vector<Ticket> userTickets;
    for (const auto& [id, ticket] : tickets) {
        if (ticket.userId == userId) {
            userTickets.push_back(ticket);
        }
    }
    return userTickets;
}

/**
 * @file TicketManager.h
 * @brief Support ticket management
 */

#ifndef TICKET_MANAGER_H
#define TICKET_MANAGER_H

#include <string>
#include <vector>

struct Ticket {
    std::string ticketId;
    std::string userId;
    std::string subject;
    std::string description;
    std::string status;
    std::string priority;
};

class TicketManager {
public:
    std::string createTicket(const std::string& userId, const std::string& subject, const std::string& description);
    Ticket getTicket(const std::string& ticketId);
    void updateTicketStatus(const std::string& ticketId, const std::string& status);
    void assignTicket(const std::string& ticketId, const std::string& agentId);
    std::vector<Ticket> getUserTickets(const std::string& userId);
    void closeTicket(const std::string& ticketId);
};

#endif

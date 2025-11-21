/**
 * @file SupportEngine.cpp
 */

#include "SupportEngine.h"
#include <iostream>

SupportEngine::SupportEngine() {}

std::string SupportEngine::handleQuery(const std::string& userId, const std::string& query) {
    std::cout << "Processing support query from " << userId << std::endl;
    
    // AI-powered response (simplified)
    if (query.find("balance") != std::string::npos) {
        return "To check your balance, use the /wallet/balance endpoint.";
    } else if (query.find("transaction") != std::string::npos) {
        return "To create a transaction, use the /transaction/create endpoint.";
    }
    
    return "Thank you for your query. A support agent will assist you shortly.";
}

std::vector<std::string> SupportEngine::getSuggestedArticles(const std::string& query) {
    std::vector<std::string> articles;
    articles.push_back("Getting Started Guide");
    articles.push_back("API Reference");
    articles.push_back("Troubleshooting Common Issues");
    return articles;
}

bool SupportEngine::escalateToHuman(const std::string& ticketId) {
    std::cout << "Escalating ticket " << ticketId << " to human agent" << std::endl;
    return true;
}

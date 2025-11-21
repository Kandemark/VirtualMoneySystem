/**
 * @file FAQManager.cpp
 */

#include "FAQManager.h"
#include <iostream>

FAQManager::FAQManager() {
    // Initialize default FAQs
    addFAQ("How do I create a wallet?", "Use the POST /wallet/create endpoint with your user ID.");
    addFAQ("What are the transaction fees?", "Transaction fees are 0.5% with a minimum of $0.50.");
    addFAQ("How long do transactions take?", "Transactions are processed in under 10ms on average.");
}

void FAQManager::addFAQ(const std::string& question, const std::string& answer) {
    FAQ faq;
    faq.question = question;
    faq.answer = answer;
    faq.category = "general";
    
    faqs.push_back(faq);
    std::cout << "FAQ added: " << question << std::endl;
}

std::vector<FAQ> FAQManager::searchFAQs(const std::string& query) const {
    std::vector<FAQ> results;
    
    for (const auto& faq : faqs) {
        if (faq.question.find(query) != std::string::npos || 
            faq.answer.find(query) != std::string::npos) {
            results.push_back(faq);
        }
    }
    
    return results;
}

std::vector<FAQ> FAQManager::getAllFAQs() const {
    return faqs;
}

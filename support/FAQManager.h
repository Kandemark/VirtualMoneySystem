/**
 * @file FAQManager.h
 * @brief FAQ management system
 */

#ifndef FAQ_MANAGER_H
#define FAQ_MANAGER_H

#include <string>
#include <vector>

struct FAQ {
    std::string question;
    std::string answer;
    std::string category;
};

class FAQManager {
public:
    void addFAQ(const FAQ& faq);
    std::vector<FAQ> searchFAQ(const std::string& query);
    std::vector<FAQ> getFAQsByCategory(const std::string& category);
    void updateFAQ(const std::string& question, const std::string& newAnswer);
};

#endif

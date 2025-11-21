/**
 * @file CardManager.h
 * @brief Virtual and physical card management
 */

#ifndef CARD_MANAGER_H
#define CARD_MANAGER_H

#include <string>
#include <map>
#include <chrono>

struct Card {
    std::string cardId;
    std::string userId;
    std::string cardNumber;
    std::string cvv;
    std::chrono::system_clock::time_point expiryDate;
    bool isActive;
    bool isVirtual;
    double spendingLimit;
};

class CardManager {
public:
    std::string issueCard(const std::string& userId, bool isVirtual);
    bool activateCard(const std::string& cardId);
    bool deactivateCard(const std::string& cardId);
    Card getCard(const std::string& cardId);
    void setSpendingLimit(const std::string& cardId, double limit);
private:
    std::map<std::string, Card> cards;
    std::string generateCardNumber();
};

#endif

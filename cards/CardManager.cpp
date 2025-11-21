#include "CardManager.h"
#include <random>

std::string CardManager::issueCard(const std::string& userId, bool isVirtual) {
    Card card;
    card.cardId = "CARD_" + std::to_string(cards.size() + 1);
    card.userId = userId;
    card.cardNumber = generateCardNumber();
    card.cvv = std::to_string(100 + (rand() % 900));
    card.expiryDate = std::chrono::system_clock::now() + std::chrono::hours(24 * 365 * 3);
    card.isActive = false;
    card.isVirtual = isVirtual;
    card.spendingLimit = 10000.0;
    
    cards[card.cardId] = card;
    return card.cardId;
}

bool CardManager::activateCard(const std::string& cardId) {
    auto it = cards.find(cardId);
    if (it != cards.end()) {
        it->second.isActive = true;
        return true;
    }
    return false;
}

bool CardManager::deactivateCard(const std::string& cardId) {
    auto it = cards.find(cardId);
    if (it != cards.end()) {
        it->second.isActive = false;
        return true;
    }
    return false;
}

Card CardManager::getCard(const std::string& cardId) {
    return cards.at(cardId);
}

void CardManager::setSpendingLimit(const std::string& cardId, double limit) {
    auto it = cards.find(cardId);
    if (it != cards.end()) {
        it->second.spendingLimit = limit;
    }
}

std::string CardManager::generateCardNumber() {
    std::string number = "4532";
    for (int i = 0; i < 12; i++) {
        number += std::to_string(rand() % 10);
    }
    return number;
}

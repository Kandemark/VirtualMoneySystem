#include "CardControls.h"

void CardControls::blockMerchantCategory(const std::string& cardId, const std::string& category) {
    blockedCategories[cardId].insert(category);
}

void CardControls::allowMerchantCategory(const std::string& cardId, const std::string& category) {
    blockedCategories[cardId].erase(category);
}

bool CardControls::isMerchantAllowed(const std::string& cardId, const std::string& category) {
    auto it = blockedCategories.find(cardId);
    if (it != blockedCategories.end()) {
        return it->second.find(category) == it->second.end();
    }
    return true;
}

void CardControls::setGeoRestriction(const std::string& cardId, const std::string& country) {
    allowedCountries[cardId].insert(country);
}
